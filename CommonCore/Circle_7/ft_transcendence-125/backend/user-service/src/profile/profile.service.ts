import { Injectable, NotFoundException } from '@nestjs/common';
import { unlink } from 'node:fs/promises';
import { join } from 'node:path';
import { PrismaService } from '../prisma/prisma.service';
import { UpdateProfileDto } from './dto/update-profile.dto';

const profileUploadDirectory =
    process.env.PROFILE_UPLOAD_DIR || join(process.cwd(), 'uploads', 'profiles');

@Injectable()
export class ProfileService
{
    constructor(private readonly prisma: PrismaService) {}

    async getPrivateProfile(userId: number)
    {
        const profile = await this.prisma.user.findUnique({
            where: {
                id: userId,
            },
            select: {
                id: true,
                username: true,
				email: true,

                avatarUrl: true,
                level: true,
                xp: true,
                wins: true,
                losses: true,
                bombplaced: true,
                enemyKill: true,
                twoFactorEnabled: true,
                createdAt: true,
                achievements: {
                    orderBy: { unlockedAt: 'asc' },
                    select: { type: true, rewardXp: true, unlockedAt: true },
                },
            },
        });

        if (!profile)
            throw new NotFoundException('User not found');

        return profile;
    }

    async getPublicProfile(userId: number)
    {
        const profile = await this.prisma.user.findUnique({
            where: {
                id: userId,
            },
            select: {
                id: true,
                username: true,

                avatarUrl: true,
                level: true,
                xp: true,
                wins: true,
                losses: true,
                bombplaced: true,
                enemyKill: true,
                achievements: {
                    orderBy: { unlockedAt: 'asc' },
                    select: { type: true, rewardXp: true, unlockedAt: true },
                },
            },
        });

        if (!profile)
            throw new NotFoundException('User not found');

        return profile;
    }

    async updateProfile(
        userId: number,
        data: UpdateProfileDto,
    ) {
        return this.prisma.user.update({
            where: {
                id: userId,
            },
            data,
            select: {
                id: true,
                username: true,
                avatarUrl: true,
                bio: true,
                level: true,
                xp: true,
                wins: true,
                losses: true,
                bombplaced: true,
                enemyKill: true,
                createdAt: true,
            },
        });
    }

    async addXp(userId: number, xp: number)
    {
        return this.prisma.user.update({
            where: {
                id: userId,
            },
            data: {
                xp: {
                    increment: xp,
                },
            },
            select: {
                id: true,
                username: true,
                avatarUrl: true,
                bio: true,
                level: true,
                xp: true,
                wins: true,
                losses: true,
                bombplaced: true,
                enemyKill: true,
                createdAt: true,
            },
        });
    }

    async updateAvatar(userId: number, filename: string) {
        const currentUser = await this.prisma.user.findUnique({
            where: { id: userId },
            select: { avatarUrl: true },
        });

        if (!currentUser)
            throw new NotFoundException('User not found');

        const profile = await this.prisma.user.update({
            where: { id: userId },
            data: { avatarUrl: `/api/user/profile/avatar/${filename}` },
            select: {
                id: true,
                username: true,
                avatarUrl: true,
                bio: true,
                level: true,
                xp: true,
                wins: true,
                losses: true,
                bombplaced: true,
                enemyKill: true,
                createdAt: true,
            },
        });

        const previousFilename = currentUser.avatarUrl?.match(
            /^\/api\/user\/profile\/avatar\/([a-zA-Z0-9-]+\.(?:jpg|jpeg|png|webp|gif))$/,
        )?.[1];
        if (previousFilename) {
            await unlink(join(profileUploadDirectory, previousFilename)).catch(() => undefined);
        }

        return profile;
    }

}