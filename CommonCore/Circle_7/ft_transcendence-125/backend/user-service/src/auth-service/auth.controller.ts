// kelde
import { Body, Controller, Get, Post, Req, Res, UseGuards } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { Response } from 'express';
import { AuthService } from './auth.service';
import { JwtAuthGuard } from './jwt-auth.guard';
import { LoginDto } from './dto/login.dto';
import { LogoutDto } from './dto/logout.dto';
import { RefreshDto } from './dto/refresh.dto';
import { RegisterDto } from './dto/register.dto';
import { VerifyTwoFactorDto } from './dto/verify-2fa.dto';

@Controller()
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  @Get('google')
  @UseGuards(AuthGuard('google'))
  googleLogin() {}

  @Get('google/callback')
  @UseGuards(AuthGuard('google'))
  async googleCallback(@Req() request: any, @Res() response: Response) {
    const session = await this.authService.loginWithGoogle(request.user);
    const frontendUrl = process.env.FRONTEND_URL ?? 'https://localhost:8443';
    const callbackUrl = new URL('/oauth/callback', frontendUrl);

    callbackUrl.searchParams.set('accessToken', session.accessToken);
    callbackUrl.searchParams.set('refreshToken', session.refreshToken);
    response.redirect(callbackUrl.toString());
  }

  @Post('register')
  register(@Body() registerDto: RegisterDto) {
    return this.authService.register(registerDto);
  }

  @Post('login')
  login(@Body() loginDto: LoginDto, @Req() request: any) {
    return this.authService.login(loginDto, request.ip ?? request.socket?.remoteAddress ?? 'unknown');
  }

  @Post('2fa/enable')
  @UseGuards(JwtAuthGuard)
  enableTwoFactor(@Req() request: any) {
    return this.authService.enableTwoFactor(request.user);
  }

  @Post('2fa/disable')
  @UseGuards(JwtAuthGuard)
  disableTwoFactor(@Req() request: any) {
    return this.authService.disableTwoFactor(request.user);
  }

  @Post('2fa/verify')
  verifyTwoFactor(@Body() verifyTwoFactorDto: VerifyTwoFactorDto) {
    return this.authService.verifyTwoFactor(verifyTwoFactorDto);
  }

  @Post('refresh')
  refresh(@Body() refreshDto: RefreshDto) {
    return this.authService.refresh(refreshDto);
  }

  @Post('logout')
  logout(@Body() logoutDto: LogoutDto) {
    return this.authService.logout(logoutDto);
  }

  @Get('me')
  @UseGuards(JwtAuthGuard)
  me(@Req() request: any) {
    return this.authService.me(request.user);
  }
}
