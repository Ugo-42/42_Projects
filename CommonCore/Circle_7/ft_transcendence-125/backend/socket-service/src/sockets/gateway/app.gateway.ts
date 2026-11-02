import {
	WebSocketGateway,
	WebSocketServer,
	SubscribeMessage,
	OnGatewayConnection,
	OnGatewayDisconnect,
	ConnectedSocket,
	MessageBody,
} from '@nestjs/websockets';

import {
	FriendRequestEvent,
	FriendAcceptedEvent,
	FriendRemovedEvent,
} from '../interfaces/friend-events.interface';

import { UseGuards } from '@nestjs/common';

import {
	Server,
	Socket,
} from 'socket.io';

import { JwtService } from '@nestjs/jwt';
import { JwtWsGuard } from './jwt-ws.guard';
import { APP_EVENTS } from '../constants/app.events';
import { JwtPayload } from '../interfaces/jwt-payload.interface';
import { PresenceService } from '../services/presence.service';

@WebSocketGateway({
	namespace: '/app',
	cors: true,
})

export class AppGateway
	implements OnGatewayConnection, OnGatewayDisconnect
{
	@WebSocketServer()
	server!: Server;

	constructor(
		private readonly jwtService: JwtService,
		private readonly presenceService: PresenceService,
	) {
		this.presenceService.onOnline(
			(userId) => {
				this.server.emit(APP_EVENTS.USER_ONLINE,{userId})
			},
		)
		this.presenceService.onOffline(
			(userId) => {
				this.server.emit(APP_EVENTS.USER_OFFLINE,{userId})
			},
		)
	}


	private emitToUser(
		userId: number,
		event: string,
		payload: unknown,
	){
		const sockets =
			this.presenceService.getUserSockets(userId,'/app',)
		if (sockets.length === 0) {
			console.log(
				`[APP] Cannot emit ${event} to user ${userId}: no /app socket`,
			)
			return false
		}
		for (const socket of sockets) {
			console.log(
				`[APP] Emit ${event} to user ${userId} (${socket.id})`,
			)
			socket.emit(
				event,
				payload,
			)
		}
		return true
	}

	// Appelé lorsqu'un client se connecte au namespace /app.
	// -------------------- HERE CHANGE -------------------- //
	handleConnection(client: Socket): void {
		try {
			const token =
				client.handshake.headers.authorization
					?.replace(/^Bearer\s+/i, '') ||
				client.handshake.auth?.token ||
				client.handshake.query.token;

			if (
				!token ||
				typeof token !== 'string'
			) {
				console.log(
					'[APP] Connection refused: missing token',
				);

				client.disconnect();
				return;
			}

			const user =
				this.jwtService.verify<JwtPayload>(
					token,
				);

			client.data.user = user;
			this.presenceService.addUser(Number(user.sub), '/app', client);

			console.log(
				`[APP] ${user.username} connected`,
			);

		} catch (error) {
			console.error(
				'[APP] WebSocket authentication failed:',
				error,
			);

			client.disconnect();
		}
	}

	// Appelé lorsqu'un client se déconnecte du namespace /app.
	handleDisconnect(client: Socket): void {
		const user =
			client.data.user as
			| JwtPayload
			| undefined;

		if (!user) {
			return;
		}

		this.presenceService.removeUser(Number(user.sub), '/app', client);

		console.log(
			`[APP] ${user.username} disconnected`,
		);
	}

	sendFriendRequestNotification(
		userId: number,
		payload: FriendRequestEvent,
	) {
		return this.emitToUser(
			userId,
			APP_EVENTS.FRIEND_REQUEST,
			payload,
		);
	}

	sendFriendAcceptedNotification(
		userId: number,
		payload: FriendAcceptedEvent,
	) {
		return this.emitToUser(
			userId,
			APP_EVENTS.FRIEND_ACCEPTED,
			payload,
		);
	}

	sendFriendRemovedNotification(
		userId: number,
		payload: FriendRemovedEvent,
	) {
		return this.emitToUser(
			userId,
			APP_EVENTS.FRIEND_REMOVED,
			payload,
		);
	}
	
	// -------------------- HERE CHANGE, REQUEST PRESENCE -------------------- //
	@UseGuards(JwtWsGuard)
	@SubscribeMessage(APP_EVENTS.PRESENCE_GET)
	handleGetPresence(
		@MessageBody()
		payload: {
			userIds: number[]
		},
	) {
		const userIds =
			Array.isArray(payload?.userIds)
				? payload.userIds
				: []

		const statuses =
			userIds.reduce<
				Record<number, boolean>
			>(
				(result, userId) => {
					result[userId] =
						this.presenceService.isOnline(
							userId,
						)

					return result
				},
				{},
			)

		return {
			success: true,
			statuses,
		}
	}

	// Rejoindre une room générale.

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(APP_EVENTS.JOIN_ROOM)
	handleJoinRoom(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		room: string,
	) {
		client.join(room);

		const user =
			client.data.user as JwtPayload;

		console.log(
			`[APP] ${user.username} joined room ${room}`,
		);

		return {
			success: true,
			room,
		};
	}


	// Quitter une room générale.

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(APP_EVENTS.LEAVE_ROOM)
	handleLeaveRoom(
		@ConnectedSocket()
		client: Socket,

		@MessageBody()
		room: string,
	) {
		client.leave(room);

		const user =
			client.data.user as JwtPayload;

		console.log(
			`[APP] ${user.username} left room ${room}`,
		);

		return {
			success: true,
			room,
		};
	}
}