// kelde
import { ConflictException, HttpException, HttpStatus, Injectable, UnauthorizedException } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { User } from '@prisma/client';
import * as nodemailer from 'nodemailer';
import { createHash, randomBytes, randomInt, randomUUID } from 'crypto';
import { PrismaService } from '../prisma/prisma.service';
import { LoginDto } from './dto/login.dto';
import { LogoutDto } from './dto/logout.dto';
import { RefreshDto } from './dto/refresh.dto';
import { RegisterDto } from './dto/register.dto';
import { VerifyTwoFactorDto } from './dto/verify-2fa.dto';

const bcrypt = require('bcrypt');

type JwtUser = {
  sub: string;
  email: string;
  username: string;
};

type TwoFactorTokenPayload = JwtUser & {
  purpose: '2fa_required';
  jti: string;
};

type PublicUser = {
  id: number;
  email: string;
  username: string;
  createdAt: Date;
  updatedAt: Date;
  twoFactorEnabled: boolean;
};

type GoogleUser = {
  email?: string;
  firstname?: string;
  lastname?: string;
};

type TwoFactorCodePurpose = 'login';

@Injectable()
export class AuthService {
  private readonly loginAttempts = new Map<string, { count: number; resetAt: number }>();

  constructor(
    private readonly prisma: PrismaService,
    private readonly jwtService: JwtService,
  ) {
  }

  async register(registerDto: RegisterDto) {
    const { email, username, password } = registerDto;

    const existingUser = await this.prisma.user.findFirst({
      where: {
        OR: [{ email }, { username }],
      },
    });

    if (existingUser) {
      throw new ConflictException('Unable to complete registration');
    }

    const passwordHash = await bcrypt.hash(password, 12);

    const createdUser = await this.prisma.user.create({
      data: {
        email,
        username,
        passwordHash,
      },
    });

    return this.createSessionResponse(createdUser);
  }

  async login(loginDto: LoginDto, ipAddress: string) {
    const { identifier, password } = loginDto;

    this.consumeLoginAttempt(ipAddress, loginDto.identifier, );

    const user = await this.prisma.user.findFirst({
      where: {
        OR: [{ email: identifier }, { username: identifier }],
      },
    });

    if (!user) {
      throw new UnauthorizedException('Invalid credentials');
    }

    const passwordMatches = await bcrypt.compare(password, user.passwordHash);

    if (!passwordMatches) {
      throw new UnauthorizedException('Invalid credentials');
    }

    this.resetLoginAttempts(ipAddress, loginDto.identifier, );

    if (user.twoFactorEnabled) {
      return this.createTwoFactorPendingResponse(user);
    }

    return this.createSessionResponse(user);
  }

  async loginWithGoogle(googleUser: GoogleUser) {
    const email = googleUser.email?.trim().toLowerCase();
    if (!email) {
      throw new UnauthorizedException('Google account has no email address');
    }

    let user = await this.prisma.user.findUnique({ where: { email } });
    if (!user) {
      const username = await this.createGoogleUsername(email, googleUser.firstname, googleUser.lastname);
      user = await this.prisma.user.create({
        data: {
          email,
          username,
          passwordHash: await bcrypt.hash(randomBytes(32).toString('hex'), 12),
        },
      });
    }

    return this.createSessionResponse(user);
  }

  async enableTwoFactor(user: JwtUser) {
    const userId = Number(user.sub);
    const dbUser = await this.prisma.user.findUnique({ where: { id: userId } });

    if (!dbUser) {
      throw new UnauthorizedException('Invalid session');
    }

    if (dbUser.twoFactorEnabled) {
      throw new HttpException('2FA is already enabled', HttpStatus.BAD_REQUEST);
    }

    await this.prisma.user.update({
      where: { id: userId },
      data: {
        twoFactorEnabled: true,
      },
    });

    return {
      twoFactorEnabled: true,
      message: '2FA enabled successfully',
    };
  }

  async disableTwoFactor(user: JwtUser) {
    const userId = Number(user.sub);
    const dbUser = await this.prisma.user.findUnique({ where: { id: userId } });

    if (!dbUser) {
      throw new UnauthorizedException('Invalid session');
    }

    if (!dbUser.twoFactorEnabled) {
      throw new HttpException('2FA is not enabled', HttpStatus.BAD_REQUEST);
    }

    await this.prisma.user.update({
      where: { id: userId },
      data: {
        twoFactorEnabled: false,
      },
    });

    return {
      twoFactorEnabled: false,
      message: '2FA disabled successfully',
    };
  }

  async verifyTwoFactor(verifyTwoFactorDto: VerifyTwoFactorDto) {
    const payload = this.verifyTwoFactorToken(verifyTwoFactorDto.twoFactorToken);
    const userId = Number(payload.sub);
    const user = await this.prisma.user.findUnique({ where: { id: userId } });

    if (!user || !user.twoFactorEnabled) {
      throw new UnauthorizedException('2FA verification failed');
    }

    await this.consumeTwoFactorCode(user, verifyTwoFactorDto.code, 'login');

    return this.createSessionResponse(user);
  }

  async refresh(refreshDto: RefreshDto) {
    const { refreshToken } = refreshDto;
    const payload = this.verifyRefreshToken(refreshToken);
    const userId = Number(payload.sub);

    const storedToken = await this.prisma.refreshToken.findUnique({
      where: { userId },
    });

    if (!storedToken || storedToken.tokenHash !== this.hashToken(refreshToken)) {
      throw new UnauthorizedException('Invalid session');
    }

    if (storedToken.expiresAt.getTime() <= Date.now()) {
      await this.prisma.refreshToken.delete({ where: { userId } });
      throw new UnauthorizedException('Invalid session');
    }

    const user = await this.prisma.user.findUnique({ where: { id: userId } });
    if (!user) {
      throw new UnauthorizedException('Invalid session');
    }

    return this.createSessionResponse(user);
  }

  async logout(logoutDto: LogoutDto) {
    const { refreshToken } = logoutDto;
    const payload = this.verifyRefreshToken(refreshToken);
    const userId = Number(payload.sub);

    await this.prisma.refreshToken.deleteMany({
      where: {
        userId,
        tokenHash: this.hashToken(refreshToken),
      },
    });

    return { message: 'Logout successful' };
  }

  async me(user: JwtUser) {
    const dbUser = await this.prisma.user.findUnique({ where: { id: Number(user.sub) } });

    if (!dbUser) {
      throw new UnauthorizedException('Invalid session');
    }

    return {
      user: {
        id: dbUser.id,
        email: dbUser.email,
        username: dbUser.username,
        twoFactorEnabled: dbUser.twoFactorEnabled,
      },
    };
  }

  private async createSessionResponse(user: User) {
    const payload = {
      sub: user.id.toString(),
      email: user.email,
      username: user.username,
    };

    const accessToken = await this.jwtService.signAsync(payload, { expiresIn: '1d' });
    const refreshToken = await this.jwtService.signAsync(
      { ...payload, jti: randomUUID() },
      {
        secret: process.env.JWT_REFRESH_SECRET ?? process.env.JWT_SECRET ?? 'dev-refresh-secret',
        expiresIn: '7d',
      },
    );

    await this.prisma.refreshToken.upsert({
      where: { userId: user.id },
      create: {
        userId: user.id,
        tokenHash: this.hashToken(refreshToken),
        expiresAt: this.getRefreshExpiryDate(),
      },
      update: {
        tokenHash: this.hashToken(refreshToken),
        expiresAt: this.getRefreshExpiryDate(),
      },
    });

    return {
      user: this.toSafeUser(user),
      accessToken,
      refreshToken,
    };
  }

  private async createGoogleUsername(email: string, firstname?: string, lastname?: string) {
    const base = `${firstname ?? ''}${lastname ?? ''}`
      .normalize('NFKD')
      .replace(/[\u0300-\u036f]/g, '')
      .replace(/[^a-zA-Z0-9]/g, '')
      .toLowerCase() || email.split('@')[0].replace(/[^a-zA-Z0-9]/g, '').toLowerCase() || 'googleuser';

    let username = base.slice(0, 20);
    let suffix = 1;
    while (await this.prisma.user.findUnique({ where: { username } })) {
      username = `${base.slice(0, 20 - String(suffix).length)}${suffix}`;
      suffix += 1;
    }
    return username;
  }

  private async createTwoFactorPendingResponse(user: User) {
    await this.sendTwoFactorCode(user, 'login');
    const payload = {
      sub: user.id.toString(),
      email: user.email,
      username: user.username,
      purpose: '2fa_required' as const,
      jti: randomUUID(),
    };

    const twoFactorToken = await this.jwtService.signAsync(payload, {
      secret: process.env.JWT_2FA_SECRET ?? process.env.JWT_SECRET ?? 'dev-auth-secret',
      expiresIn: '5m',
    });

    return {
      status: '2fa_required',
      twoFactorRequired: true,
      twoFactorToken,
      user: {
        id: user.id,
        email: user.email,
        username: user.username,
      },
    };
  }

  private verifyRefreshToken(refreshToken: string): JwtUser {
    try {
      return this.jwtService.verify<JwtUser>(refreshToken, {
        secret: process.env.JWT_REFRESH_SECRET ?? process.env.JWT_SECRET ?? 'dev-refresh-secret',
      });
    } catch {
      throw new UnauthorizedException('Invalid session');
    }
  }

  private verifyTwoFactorToken(twoFactorToken: string): TwoFactorTokenPayload {
    try {
      const payload = this.jwtService.verify<TwoFactorTokenPayload>(twoFactorToken, {
        secret: process.env.JWT_2FA_SECRET ?? process.env.JWT_SECRET ?? 'dev-auth-secret',
      });

      if (payload.purpose !== '2fa_required') {
        throw new UnauthorizedException('Invalid 2FA token');
      }

      return payload;
    } catch {
      throw new UnauthorizedException('Invalid 2FA token');
    }
  }

  private toSafeUser(user: User): PublicUser {
    return {
      id: user.id,
      email: user.email,
      username: user.username,
      createdAt: user.createdAt,
      updatedAt: user.updatedAt,
      twoFactorEnabled: user.twoFactorEnabled,
    };
  }

  private async sendTwoFactorCode(user: User, purpose: TwoFactorCodePurpose) {
    const code = randomInt(100000, 1000000).toString();
    const expiresAt = new Date(Date.now() + 5 * 60 * 1000);

    await this.prisma.user.update({
      where: { id: user.id },
      data: {
        twoFactorCodeHash: this.hashToken(code),
        twoFactorCodeExpiresAt: expiresAt,
        twoFactorCodePurpose: purpose,
      },
    });

    try {
      await this.createMailTransporter().sendMail({
        from: process.env.SMTP_FROM ?? process.env.SMTP_USER,
        to: user.email,
        subject: 'Your ft_transcendence verification code',
        text: `Your verification code is ${code}. It expires in 5 minutes.`,
      });
    } catch (error) {
      console.error(
        '[2FA] Email delivery failed:',
        error instanceof Error ? error.message : error,
      );
      await this.prisma.user.update({
        where: { id: user.id },
        data: {
          twoFactorCodeHash: null,
          twoFactorCodeExpiresAt: null,
          twoFactorCodePurpose: null,
        },
      });
      throw new HttpException('Unable to send verification email', HttpStatus.SERVICE_UNAVAILABLE);
    }

    return { message: 'Verification code sent by email', expiresInSeconds: 300 };
  }

  private async consumeTwoFactorCode(user: User, code: string, purpose: TwoFactorCodePurpose) {
    if (
      !user.twoFactorCodeHash ||
      !user.twoFactorCodeExpiresAt ||
      user.twoFactorCodePurpose !== purpose ||
      user.twoFactorCodeExpiresAt.getTime() <= Date.now() ||
      user.twoFactorCodeHash !== this.hashToken(code)
    ) {
      throw new UnauthorizedException('Invalid or expired 2FA code');
    }

    await this.prisma.user.update({
      where: { id: user.id },
      data: {
        twoFactorCodeHash: null,
        twoFactorCodeExpiresAt: null,
        twoFactorCodePurpose: null,
      },
    });
  }

  private createMailTransporter() {
    const host = process.env.SMTP_HOST?.trim();
    const port = Number(process.env.SMTP_PORT ?? 587);
    const user = process.env.SMTP_USER?.trim();
    const pass = process.env.SMTP_PASS;

    if (!host || !user || !pass) {
      throw new HttpException('SMTP configuration is incomplete', HttpStatus.INTERNAL_SERVER_ERROR);
    }

    return nodemailer.createTransport({
      host,
      port,
      secure: process.env.SMTP_SECURE === 'true',
      auth: { user, pass },
    });
  }

  private hashToken(token: string) {
    return createHash('sha256').update(token).digest('hex');
  }

  private getRefreshExpiryDate() {
    return new Date(Date.now() + 7 * 24 * 60 * 60 * 1000);
  }

  private consumeLoginAttempt(
    ipAddress: string,
    identifier: string,
  ) {

    const key =
      `${ipAddress}:${identifier.toLowerCase()}`

    const now = Date.now()
    const current =
      this.loginAttempts.get(key)

    if (!current || current.resetAt <= now) {
      this.loginAttempts.set(key, {
        count: 1,
        resetAt: now + 15 * 60 * 1000,
      })
      return
    }

    if (current.count >= 5) {
      throw new HttpException(
        "Too many attempts. Please try again later.",
        HttpStatus.TOO_MANY_REQUESTS,
      )
    }

    this.loginAttempts.set(key, {
      count: current.count + 1,
      resetAt: current.resetAt,
    })
  }

  private resetLoginAttempts(
    ipAddress: string,
    identifier: string,
  ) {

    const key =
      `${ipAddress}:${identifier.toLowerCase()}`

    this.loginAttempts.delete(key)
  }
}
