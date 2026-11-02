import {
	Body,
	Controller,
	Get,
	Post,
} from '@nestjs/common';

import { AppGateway } from './sockets/gateway/app.gateway';

import {
	FriendRequestEvent,
	FriendAcceptedEvent,
	FriendRemovedEvent,
} from './sockets/interfaces/friend-events.interface';

@Controller()
export class AppController {
	constructor(
		private readonly appGateway: AppGateway,
	) {}

	@Get('health')
	getHealth() {
		return {
			status: 'ok',
			service: 'socket-service',
		};
	}

	@Post('internal/friends/request')
	notifyFriendRequest(
		@Body()
		body: {
			userId: number;
			payload: FriendRequestEvent;
		},
	) {
		return {
			sent:
				this.appGateway
					.sendFriendRequestNotification(
						body.userId,
						body.payload,
					),
		};
	}

	@Post('internal/friends/accepted')
	notifyFriendAccepted(
		@Body()
		body: {
			userId: number;
			payload: FriendAcceptedEvent;
		},
	) {
		return {
			sent:
				this.appGateway
					.sendFriendAcceptedNotification(
						body.userId,
						body.payload,
					),
		};
	}

	@Post('internal/friends/removed')
	notifyFriendRemoved(
		@Body()
		body: {
			userId: number;
			payload: FriendRemovedEvent;
		},
	) {
		return {
			sent:
				this.appGateway
					.sendFriendRemovedNotification(
						body.userId,
						body.payload,
					),
		};
	}
}
