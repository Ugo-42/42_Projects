import { Body, Controller, Get, Param, Post } from '@nestjs/common';
import { GameManagerService } from './game-manager.service';
import type { Direction } from './types';

interface DirectionDto {
	playerId: number;
	dirX: number;
	dirY: number;
}

interface StopDto {
	playerId: number;
}

@Controller('internal/game')
export class GameController {
	constructor(private readonly gameManagerService: GameManagerService) {}

	@Get(':gameId/state')
	getState(@Param('gameId') gameId: string) {
		return this.gameManagerService.getGameState(gameId) ?? { error: 'game_not_found' };
	}

	@Post(':gameId/move')
	move(@Param('gameId') gameId: string, @Body() dto: DirectionDto) {
		const direction: Direction = { dirX: dto.dirX, dirY: dto.dirY };
		return this.gameManagerService.setPlayerDirection(gameId, dto.playerId, direction);
	}

	@Post(':gameId/stop')
	stop(@Param('gameId') gameId: string, @Body() dto: StopDto) {
		return this.gameManagerService.stopPlayer(gameId, dto.playerId);
	}

	@Post(':gameId/disconnect')
	disconnect(@Param('gameId') gameId: string, @Body() dto: StopDto) {
		this.gameManagerService.disconnectPlayer(gameId, dto.playerId);
		return { success: true };
	}
}
