import {
    BadRequestException,
    ConflictException,
    Injectable,
    NotFoundException,
    UnauthorizedException,
} from '@nestjs/common';

import { UpdateUserDto } from './dto/update-user.dto';
import { PrismaService } from '../prisma/prisma.service';

const achievementRewards = {
    PLAY_GAME: 100,
    WIN_GAME: 250,
    PLACE_10_BOMBS: 150,
} as const;

const bcrypt = require('bcrypt');

@Injectable()
export class UserService {
    constructor(
        private readonly prisma: PrismaService,
    ) {}

    async recordGameResult(
        userId: number,
        result: 'win' | 'loss' | 'draw',
        bombplaced: number,
        enemyKill: number,
        xp: number,
    ) {
        return this.prisma.$transaction(async (tx) => {
            const user = await tx.user.update({
                where: { id: userId },
                data: {
                    wins: result === 'win' ? { increment: 1 } : undefined,
                    losses: result === 'loss' ? { increment: 1 } : undefined,
                    bombplaced: { increment: bombplaced },
                    enemyKill: { increment: enemyKill },
                    xp: { increment: xp },
                },
                select: {
                    id: true,
                    wins: true,
                    losses: true,
                    bombplaced: true,
                    enemyKill: true,
                    xp: true,
                },
            });

            const types = ['PLAY_GAME'];
            if (result === 'win') types.push('WIN_GAME');
            if (user.bombplaced >= 10) types.push('PLACE_10_BOMBS');

            let achievementXp = 0;
            for (const type of types as Array<keyof typeof achievementRewards>) {
                const created = await tx.userAchievement.createMany({
                    data: [{
                        userId,
                        type,
                        rewardXp: achievementRewards[type],
                    }],
                    skipDuplicates: true,
                });
                if (created.count > 0) achievementXp += achievementRewards[type];
            }

            if (achievementXp > 0) {
                await tx.user.update({
                    where: { id: userId },
                    data: { xp: { increment: achievementXp } },
                });
            }

            return {
                ...user,
                xp: user.xp + achievementXp,
            };
        });
    }

    async findById(userId: number) {
        const user = await this.prisma.user.findUnique({
            where: {
                id: userId,
            },
            select: {
                id: true,
                username: true,
                email: true,
                createdAt: true,
                updatedAt: true,
            },
        });

        if (!user) {
            throw new NotFoundException('User not found');
        }

        return user;
    }

    async findByUsername(username: string) {
        return this.prisma.user.findUnique({
            where: {
                username,
            },
            select: {
                id: true,
                username: true,
                createdAt: true,
            },
        });
    }

    async getLeaderboard() {
        const users = await this.prisma.user.findMany({
            orderBy: {
                xp: 'desc',
            },
            select: {
                id: true,
                username: true,
                avatarUrl: true,
                xp: true,
            },
        });

        return users.map((user) => ({
            userId: user.id,
            username: user.username,
            avatarUrl: user.avatarUrl,
            value: user.xp,
        }));
    }

    async updateUser(
        userId: number,
        data: UpdateUserDto,
    ) {
        const user = await this.prisma.user.findUnique({
            where: {
                id: userId,
            },
        });

        if (!user) {
            throw new NotFoundException('User not found');
        }

        if (data.username && data.username !== user.username) {
            const existingUsername =
                await this.prisma.user.findUnique({
                    where: {
                        username: data.username,
                    },
                });

            if (existingUsername) {
                throw new ConflictException(
                    'Username already in use',
                );
            }
        }

        if (data.email && data.email !== user.email) {
            const existingEmail =
                await this.prisma.user.findUnique({
                    where: {
                        email: data.email,
                    },
                });

            if (existingEmail) {
                throw new ConflictException(
                    'Email already in use',
                );
            }
        }

        let passwordHash: string | undefined;

        if (data.newPassword) {
            if (!data.currentPassword) {
                throw new BadRequestException(
                    'Current password is required',
                );
            }

            const passwordMatches =
                await bcrypt.compare(
                    data.currentPassword,
                    user.passwordHash,
                );

            if (!passwordMatches) {
                throw new UnauthorizedException(
                    'Current password is incorrect',
                );
            }

            passwordHash =
                await bcrypt.hash(
                    data.newPassword,
                    12,
                );
        }

        const updateData: {
            username?: string
            email?: string
            passwordHash?: string
        } = {}

        if (
            data.username &&
            data.username !== user.username
        ) {
            updateData.username = data.username
        }

        if (
            data.email &&
            data.email !== user.email
        ) {
            updateData.email = data.email
        }

        if (passwordHash) {
            updateData.passwordHash = passwordHash
        }

        if (Object.keys(updateData).length === 0) {
            throw new BadRequestException(
                'No changes to apply',
            )
        }

        return this.prisma.user.update({
                where: {
                    id: userId,
                },
                data: updateData,
                select: {
                    id: true,
                    username: true,
                    email: true,
                    createdAt: true,
                    updatedAt: true,
                },
            });
    }

    async deleteUser(userId: number) {
        const user = await this.prisma.user.findUnique({
            where: {
                id: userId,
            },
        });

        if (!user) {
            throw new NotFoundException('User not found');
        }

        await this.prisma.user.delete({
            where: {
                id: userId,
            },
        });

        return {
            message: 'User deleted successfully',
        };
    }

    async searchUsers(
        username: string,
        currentUserId: number,
    ) {
        const friendships =
            await this.prisma.friendship.findMany({
                where: {
                    OR: [
                        { senderId: currentUserId },
                        { receiverId: currentUserId },
                    ],
                },
                select: {
                    senderId: true,
                    receiverId: true,
                },
            })

        const excludedIds = friendships.map(
            (friendship) =>
                friendship.senderId === currentUserId
                    ? friendship.receiverId
                    : friendship.senderId,
        )

        return this.prisma.user.findMany({
            where: {
                id: {
                    notIn: [
                        currentUserId,
                        ...excludedIds,
                    ],
                },
                username: {
                    contains: username,
                    mode: "insensitive",
                },
            },
            select: {
                id: true,
                username: true,
                avatarUrl: true,
            },
            take: 10,
        })
    }
}