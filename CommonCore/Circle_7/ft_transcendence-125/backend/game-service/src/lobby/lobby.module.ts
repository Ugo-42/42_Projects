import { Module } from '@nestjs/common';

import { LobbyController } from './lobby.controller';
import { LobbyService } from './lobby.service';
import { JwtStrategy } from '../auth/jwt.strategy';
import { GameSocketModule } from '../sockets/game-socket.module'
import { GameLogicModule } from 'src/game-logic/game-logic.module';


@Module({
	imports: [
		GameSocketModule,
		GameLogicModule,
	],

	controllers: [
		LobbyController
	],
	providers: [
		LobbyService,
		JwtStrategy
	]
})
export class LobbyModule {}
