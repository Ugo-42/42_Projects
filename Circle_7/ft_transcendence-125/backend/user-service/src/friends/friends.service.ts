import {
    BadRequestException,
    Injectable,
    NotFoundException,
} from '@nestjs/common';
import { PrismaService } from '../prisma/prisma.service';

@Injectable()
export class FriendsService {
    constructor(private readonly prisma: PrismaService) {}

    private async notifySocket(
        path: string,
        body: unknown,
    ) {
        try {
            const response = await fetch(
                `http://socket-service:3004${path}`,
                {
                    method: 'POST',
                    headers: {
                        'Content-Type':
                            'application/json',
                    },
                    body: JSON.stringify(body),
                },
            );

            if (!response.ok) {
                console.error(
                    `[FRIENDS] Socket notification failed: ${response.status}`,
                );
            }
        } catch (error) {
            console.error(
                '[FRIENDS] Socket service unreachable:',
                error,
            );
        }
    }

    async sendRequest(senderId: number, receiverId: number) {
        if (senderId === receiverId) {
            throw new BadRequestException(
                'You cannot send a friend request to yourself',
            );
        }

        const receiver = await this.prisma.user.findUnique({
            where: { id: receiverId },
        });

        if (!receiver) {
            throw new NotFoundException('User not found');
        }

        const existingRequest = await this.prisma.friendship.findFirst({
            where: {
                OR: [
                    {
                        senderId,
                        receiverId,
                    },
                    {
                        senderId: receiverId,
                        receiverId: senderId,
                    },
                ],
            },
        });

        if (existingRequest) {
            throw new BadRequestException(
                'A friendship or friend request already exists',
            );
        }

        const friendship =
            await this.prisma.friendship.create({
                data: {
                    senderId,
                    receiverId,
                },
                include: {
                    sender: {
                        select: {
                            id: true,
                            username: true,
                            avatarUrl: true,
                        },
                    },
                },
            });

        await this.notifySocket(
            '/internal/friends/request',
            {
                userId: receiverId,
                payload: {
                    id: friendship.id,
                    sender: friendship.sender,
                },
            },
        );

        return friendship;
    }

    async getReceivedRequests(userId: number) {
        return this.prisma.friendship.findMany({
            where: {
                receiverId: userId,
                status: 'PENDING',
            },
            include: {
                sender: {
                    select: {
                        id: true,
                        username: true,
                        avatarUrl: true,
                    },
                },
            },
            orderBy: {
                createdAt: 'desc',
            },
        });
    }

    async acceptRequest(userId: number, friendshipId: number) {
        const request = await this.prisma.friendship.findUnique({
            where: {
                id: friendshipId,
            },
        });

        if (!request) {
            throw new NotFoundException('Friend request not found');
        }

        if (request.receiverId !== userId) {
            throw new BadRequestException(
                'You cannot accept this friend request',
            );
        }

        if (request.status !== 'PENDING') {
            throw new BadRequestException(
                'This friend request is no longer pending',
            );
        }

        const friendship =
            await this.prisma.friendship.update({
                where: {
                    id: friendshipId,
                },
                data: {
                    status: 'ACCEPTED',
                },
            });

        const acceptedBy =
            await this.prisma.user.findUnique({
                where: {
                    id: userId,
                },
                select: {
                    id: true,
                    username: true,
                    avatarUrl: true,
                },
            });

        const sender =
            await this.prisma.user.findUnique({
                where: {
                    id: request.senderId,
                },
                select: {
                    id: true,
                    username: true,
                    avatarUrl: true,
                },
            })

        if (acceptedBy) {
            await this.notifySocket(
                '/internal/friends/accepted',
                {
                    userId: request.senderId,
                    payload: acceptedBy,
                },
            );
        }
        if (sender) {
            await this.notifySocket(
                '/internal/friends/accepted',
                {
                    userId,
                    payload: sender,
                },
            )
        }
        return friendship;
    }

    async declineRequest(userId: number, friendshipId: number) {
        const request = await this.prisma.friendship.findUnique({
            where: {
                id: friendshipId,
            },
        });

        if (!request) {
            throw new NotFoundException('Friend request not found');
        }

        if (request.receiverId !== userId) {
            throw new BadRequestException(
                'You cannot decline this friend request',
            );
        }

        if (request.status !== 'PENDING') {
            throw new BadRequestException(
                'This friend request is no longer pending',
            );
        }

        return this.prisma.friendship.delete({
            where: {
                id: friendshipId,
            },
        });
    }

    async getFriends(userId: number) {
        const friendships = await this.prisma.friendship.findMany({
            where: {
                status: 'ACCEPTED',
                OR: [
                    { senderId: userId },
                    { receiverId: userId },
                ],
            },
            include: {
                sender: {
                    select: {
                        id: true,
                        username: true,
                        avatarUrl: true,
                    },
                },
                receiver: {
                    select: {
                        id: true,
                        username: true,
                        avatarUrl: true,
                    },
                },
            },
        });

        return friendships.map((friendship) => {
            return friendship.senderId === userId
                ? friendship.receiver
                : friendship.sender;
        });
    }

    async areFriends(userId: number, friendId: number) {
        const friendship = await this.prisma.friendship.findFirst({
            where: {
                status: 'ACCEPTED',
                OR: [
                    {
                        senderId: userId,
                        receiverId: friendId,
                    },
                    {
                        senderId: friendId,
                        receiverId: userId,
                    },
                ],
            },
            select: { id: true },
        });

        return { areFriends: friendship !== null };
    }

    async removeFriend(userId: number, friendId: number) {
        const friendship = await this.prisma.friendship.findFirst({
            where: {
                status: 'ACCEPTED',
                OR: [
                    {
                        senderId: userId,
                        receiverId: friendId,
                    },
                    {
                        senderId: friendId,
                        receiverId: userId,
                    },
                ],
            },
        });

        if (!friendship) {
            throw new NotFoundException('Friendship not found');
        }

        const deleted =
            await this.prisma.friendship.delete({
                where: {
                    id: friendship.id,
                },
            });

        await this.notifySocket(
            '/internal/friends/removed',
            {
                userId: friendId,
                payload: {
                    userId,
                },
            },
        );

        return deleted;
    }
}