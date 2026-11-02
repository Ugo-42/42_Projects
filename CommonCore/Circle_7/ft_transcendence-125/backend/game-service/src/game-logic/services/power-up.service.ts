import { Injectable } from '@nestjs/common';

import { GameState } from '../models/game-state';
import {
	PowerUp,
	PowerUpType,
} from '../models/power-up';

import { PlayerService } from './player.service';

const POWER_UP_WEIGHTS: Record<PowerUpType, number> = {
	bomb_plus: 22,
	kick: 10,
	speed_plus: 22,
	flame_plus: 22,

	bomb_minus: 8,
	speed_minus: 8,
	flame_minus: 8,
}

@Injectable()
export class PowerUpService {

	private readonly DROP_CHANCE = 0.35;


	constructor(
		private readonly playerService: PlayerService,
	) {}


	createPowerUp(
		game: GameState,
		type: PowerUpType,
		x: number,
		y: number,
	): PowerUp {

		const powerUp = new PowerUp(
			type,
			x,
			y,
		);

		game.powerUps.set(
			powerUp.id,
			powerUp,
		);

		return powerUp;
	}


	trySpawnPowerUp(
		game: GameState,
		x: number,
		y: number,
	): PowerUp | undefined {
		if (Math.random() >= this.DROP_CHANCE) {
			return undefined;
		}

		return this.createPowerUp(
			game,
			this.getRandomPowerUpType(),
			x,
			y,
		);
	}


	getPowerUps(game: GameState): PowerUp[] {
		return Array.from(game.powerUps.values());
	}


	getPowerUp(
		game: GameState,
		id: string,
	): PowerUp | undefined {
		return game.powerUps.get(id);
	}


	getPowerUpAt(
		game: GameState,
		x: number,
		y: number,
	): PowerUp | undefined {
		return this.getPowerUps(game).find(
			(powerUp) =>
				powerUp.x === x &&
				powerUp.y === y &&
				!powerUp.isCollected(),
		);
	}


	collectPowerUp(
		game: GameState,
		playerId: number,
		id: string,
	): PowerUp | undefined {
		const player = this.playerService.getPlayer(game, playerId);
		const powerUp = game.powerUps.get(id);

		if (
			!player ||
			!player.alive ||
			!powerUp ||
			powerUp.isCollected() ||
			player.x !== powerUp.x ||
			player.y !== powerUp.y
		) {
			return undefined;
		}

		powerUp.collect();
		game.powerUps.delete(id);
		this.playerService.applyPowerUp(
			game,
			playerId,
			powerUp.type,
		);

		return powerUp;
	}


	removePowerUp(
		game: GameState,
		id: string,
	): void {
		game.powerUps.delete(id);
	}


	private getRandomPowerUpType(): PowerUpType {
		const entries = Object.entries(POWER_UP_WEIGHTS)

		const totalWeight = entries.reduce(
			(sum, [, weight]) => sum + weight,
			0,
		)
		let random = Math.random() * totalWeight
		for (const [type, weight] of entries) {
			random -= weight
			if (random < 0) {
				return type as PowerUpType
			}
		}

		return entries[entries.length - 1][0] as PowerUpType
	}
}