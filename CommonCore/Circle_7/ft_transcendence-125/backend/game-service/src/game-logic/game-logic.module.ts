import { Module } from '@nestjs/common';

import { BombService } from './services/bomb.service';
import { MapService } from './services/map.service';
import { PlayerService } from './services/player.service';
import { PowerUpService } from './services/power-up.service';
import { GameController } from './game.controller';
import { GameManagerService } from './game-manager.service';
import { MovementService } from './services/movement.service';
import { GameEngineEventsService } from './services/game-engine-events.service'
import { UserStatsService } from './services/user-stats.service';
import { XpService } from './services/xp.service';


@Module({
	controllers: [
		GameController,
	],

	providers: [
		GameManagerService,
		GameEngineEventsService,

		PlayerService,
		MapService,
		MovementService,
		BombService,
		PowerUpService,
		UserStatsService,
		XpService,
	],

	exports: [
		GameManagerService,
		GameEngineEventsService
	],
})
export class GameLogicModule {}