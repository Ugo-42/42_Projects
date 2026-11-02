import { Module } from '@nestjs/common'
import { JwtModule } from '@nestjs/jwt'
import { GameLogicModule } from 'src/game-logic/game-logic.module'
import { GameGateway } from './gateway/game.gateway'
import { JwtWsGuard } from './gateway/jwt-ws.guard'
import { LobbyRealtimeService } from './services/lobby-realtime.service'

@Module({
	imports: [
		GameLogicModule,
		
		JwtModule.register({
			secret:
				process.env.JWT_SECRET ||
				'development_secret',
		}),
	],

	providers: [
		GameGateway,
		JwtWsGuard,
		LobbyRealtimeService,
	],

	exports: [
		LobbyRealtimeService,
	],
})
export class GameSocketModule {}