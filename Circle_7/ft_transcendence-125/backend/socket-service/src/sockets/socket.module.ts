import { Module }
	from '@nestjs/common';

import { JwtModule }
	from '@nestjs/jwt';

import { AppGateway }
	from './gateway/app.gateway';

import { ChatGateway }
	from './gateway/chat.gateway';

import { JwtWsGuard }
	from './gateway/jwt-ws.guard';

import { PresenceService }
	from './services/presence.service';

import { FriendshipService }
	from './services/friendship.service';

import { LobbyService }
	from './services/lobby.service';


@Module({
	imports: [
		JwtModule.register({
			secret:
				process.env.JWT_SECRET || 'development_secret',
		}),
	],

	providers: [
		AppGateway,
		ChatGateway,
		JwtWsGuard,
		PresenceService,
		FriendshipService,
		LobbyService,
	],
	exports: [
		AppGateway,
	],
})
export class SocketModule {}