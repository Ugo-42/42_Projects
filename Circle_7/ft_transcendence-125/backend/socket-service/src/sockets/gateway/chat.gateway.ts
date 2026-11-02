import {
	WebSocketGateway,
	WebSocketServer,
	SubscribeMessage,
	OnGatewayConnection,
	OnGatewayDisconnect,
	ConnectedSocket,
	MessageBody,
} from '@nestjs/websockets';

import { Injectable, UseGuards } from '@nestjs/common';

import {
	Namespace,
	Socket,
} from 'socket.io';

import { JwtService } from '@nestjs/jwt';

import { JwtWsGuard } from './jwt-ws.guard';

import { PresenceService } from '../services/presence.service';
import { FriendshipService } from '../services/friendship.service';
import { JwtPayload } from '../interfaces/jwt-payload.interface';

import { CHAT_EVENTS } from '../constants/chat.events';
import { SendMessageDto } from '../dto/send-message.dto';
import { ChatMessage } from '../interfaces/chat-message.interface';
import { LobbyService } from '../services/lobby.service';


@WebSocketGateway({
	namespace: '/chat',
	cors: true,
})
@Injectable()
export class ChatGateway
	implements OnGatewayConnection, OnGatewayDisconnect
{
	private readonly history =
		new Map<string, ChatMessage[]>();

	private readonly maxHistorySize = 100;

	@WebSocketServer()
	server!: Namespace;

	constructor(
		private readonly jwtService: JwtService,
		private readonly presenceService: PresenceService,
		private readonly friendshipService: FriendshipService,
		private readonly lobbyService: LobbyService,
	) {
		this.presenceService.onOffline((userId) => {
			this.cleanupPrivateRoomsForUser(userId);
		});
	}

	handleConnection(client: Socket): void {
		try {
			const token =
				client.handshake.headers.authorization
					?.replace(/^Bearer\s+/i, '') ||
				client.handshake.auth?.token ||
				client.handshake.query.token;

			if (!token || typeof token !== 'string') {
				client.disconnect();
				return;
			}

			const user =
				this.jwtService.verify<JwtPayload>(token);
			client.data.user = user;
			client.data.chatToken = token;
			this.presenceService.addUser(Number(user.sub), '/chat', client);
		} catch {
			client.disconnect();
		}
	}

	handleDisconnect(client: Socket): void {
		const user = client.data.user as JwtPayload | undefined;
		if (user) {
			this.presenceService.removeUser(Number(user.sub), '/chat', client);
		}

		for (const room of client.rooms) {
			if (room !== client.id) {
				this.cleanupRoom(room);
			}
		}
	}


	// Rejoindre une room de chat.
	@UseGuards(JwtWsGuard)
	@SubscribeMessage(CHAT_EVENTS.JOIN)
	async handleJoinRoom(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		room: string,
	) {
		if (!this.isValidLobbyRoom(room)) {
			return {
				success: false,
				error: 'INVALID_ROOM',
			};
		}

		const lobbyId = this.getLobbyId(room);

		const isMember = await this.lobbyService.isLobbyMember(
			lobbyId,
			this.getToken(client),
		);

		if (!isMember) {
			return {
				success: false,
				error: 'NOT_LOBBY_MEMBER',
			};
		}

		client.join(room);
		this.emitHistory(client, room);

		console.log(
			`[CHAT] User ${client.data.user?.username} joined ${room}`,
		);

		return {
			success: true,
			room,
		};
	}

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(CHAT_EVENTS.JOIN_PRIVATE)
	async handleJoinPrivateRoom(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		payload: { userId: number },
	) {
		const currentUserId = this.getUserId(client);
		const otherUserId = Number(payload?.userId);

		if (!Number.isInteger(otherUserId) || otherUserId <= 0 || otherUserId === currentUserId) {
			return {
				success: false,
				error: 'INVALID_USER',
			};
		}

		const areFriends = await this.friendshipService.areFriends(
			otherUserId,
			this.getToken(client),
		);
		if (!areFriends) {
			return {
				success: false,
				error: 'FRIENDS_ONLY',
			};
		}

		const room = this.getPrivateRoom(currentUserId, otherUserId);
		client.join(room);
		this.emitHistory(client, room);

		return {
			success: true,
			room,
			online: this.presenceService.isOnline(otherUserId),
		};
	}


	// Quitter une room de chat.
	@UseGuards(JwtWsGuard)
	@SubscribeMessage(CHAT_EVENTS.LEAVE)
	handleLeaveRoom(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		room: string,
	) {
		client.leave(room);
		this.cleanupRoom(room);

		console.log(
			`[CHAT] User ${client.data.user?.username} left ${room}`,
		);

		return {
			success: true,
			room,
		};
	}


	// Envoyer un message dans une room.
	@UseGuards(JwtWsGuard)
	@SubscribeMessage(CHAT_EVENTS.MESSAGE)
	async handleChatMessage(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		payload: SendMessageDto,
	) {
		const { room, message } = payload;


		// Vérifie que l'utilisateur est dans la room.
		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_ROOM',
			};
		}

		if (this.isPrivateRoom(room)) {
			const privateUserIds = this.getPrivateUserIds(room);
			const currentUserId = this.getUserId(client);
			const otherUserId = privateUserIds.find((userId) => userId !== currentUserId);

			if (
				!privateUserIds.includes(currentUserId) ||
				otherUserId === undefined ||
				!await this.friendshipService.areFriends(otherUserId, this.getToken(client))
			) {
				return {
					success: false,
					error: 'FRIENDS_ONLY',
				};
			}
		}


		const chatMessage: ChatMessage = {
			room,
			userId: Number(client.data.user?.sub),
			username: client.data.user?.username,
			message,
			date: new Date(),
		};


		// Envoie le message a tous les utilisateurs de la room.
		this.server.to(room).emit(
			CHAT_EVENTS.RECEIVED,
			chatMessage,
		);

		const messages = this.history.get(room) ?? [];
		messages.push(chatMessage);
		if (messages.length > this.maxHistorySize) {
			messages.splice(0, messages.length - this.maxHistorySize);
		}
		this.history.set(room, messages);

		return {
			success: true,
		};
	}

	private emitHistory(client: Socket, room: string): void {
		client.emit(
			CHAT_EVENTS.HISTORY,
			{
				room,
				messages: this.history.get(room) ?? [],
			},
		);
	}

	private getUserId(client: Socket): number {
		return Number((client.data.user as JwtPayload).sub);
	}

	private getToken(client: Socket): string {
		return client.data.chatToken as string;
	}

	private getPrivateRoom(firstUserId: number, secondUserId: number): string {
		const userIds = [firstUserId, secondUserId].sort((left, right) => left - right);
		return `private:${userIds[0]}:${userIds[1]}`;
	}

	private isValidLobbyRoom(room: string): boolean {
		return /^lobby:[0-9a-fA-F-]{36}$/.test(room);
	}

	private getLobbyId(room: string): string {
		return room.slice('lobby:'.length);
	}

	private isPrivateRoom(room: string): boolean {
		return /^private:\d+:\d+$/.test(room);
	}

	private getPrivateUserIds(room: string): number[] {
		return room
			.split(':')
			.slice(1)
			.map((userId) => Number(userId));
	}

	private cleanupRoom(room: string): void {
		if (room.startsWith('private:')) {
			return;
		}

		const roomMembers = this.server.adapter.rooms.get(room)

		if (roomMembers && roomMembers.size > 0) {
			return;
		}

		this.history.delete(room);
	}

	private cleanupPrivateRoomsForUser(userId: number): void {
		for (const room of this.history.keys()) {
			if (!room.startsWith('private:') || !room.split(':').includes(String(userId))) {
				continue;
			}
			this.cleanupRoom(room);
		}
	}


	// Utilisateur en train d'écrire.
	@UseGuards(JwtWsGuard)
	@SubscribeMessage(CHAT_EVENTS.TYPING)
	handleTyping(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		payload: {
			room: string;
		},
	) {
		const { room } = payload;


		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_ROOM',
			};
		}


		client.to(room).emit(
			CHAT_EVENTS.TYPING,
			{
				userId: Number(client.data.user?.sub),
			},
		);

		return {
			success: true,
		};
	}


	// Utilisateur arrête d'écrire.
	@UseGuards(JwtWsGuard)
	@SubscribeMessage(CHAT_EVENTS.STOP_TYPING)
	handleStopTyping(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		payload: {
			room: string;
		},
	) {
		const { room } = payload;


		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_ROOM',
			};
		}


		client.to(room).emit(
			CHAT_EVENTS.STOP_TYPING,
			{
				userId: Number(client.data.user?.sub),
			},
		);

		return {
			success: true,
		};
	}
}
