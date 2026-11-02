import { Injectable } from '@nestjs/common';

import { Bomb } from '../models/bomb';
import { GameState } from '../models/game-state';
import { PowerUpDto } from '../models/gameplay-dto';
import { GameMap } from '../models/map';
import { PowerUp } from '../models/power-up';

import { MapService } from './map.service';
import { PlayerService } from './player.service';
import { PowerUpService } from './power-up.service';


export interface ExplosionCell {
	x: number;
	y: number;
}

export interface ExplosionData {
	bombId: string;
	playerId: number;
	center: ExplosionCell;
	cells: ExplosionCell[];
}

export interface ExplosionResult {
	gameId: string;
	bombId: string;
	playerId: number;

	explosions: ExplosionData[];

	destroyedBlocks: ExplosionCell[];
	powerUps: PowerUpDto[];
	spawnedPowerUps: PowerUpDto[];
	hitPlayers: number[];
	deadPlayers: number[];
	chainReactionBombIds: string[];
}


@Injectable()
export class BombService {

	constructor(
		private readonly playerService: PlayerService,
		private readonly mapService: MapService,
		private readonly powerUpService: PowerUpService,
	) {}


	createBomb(
		game: GameState,
		//state: GameState,
		playerId: number,
		x: number,
		y: number,
		range?: number,
		damage: number = 1,
		explosionDelay: number = 2500,
	): Bomb | undefined {
		const player = this.playerService.getPlayer(game, playerId);
		const bombRange = range ?? player?.flameRange ?? 0;

		if (
			!player ||
			!player.alive ||
			player.availableBombs <= 0 ||
			!Number.isInteger(x) ||
			!Number.isInteger(y) ||
			!Number.isInteger(bombRange) ||
			bombRange < 1 ||
			damage <= 0 ||
			explosionDelay < 0 ||
			!this.mapService.isInside(game.map, x, y) ||
			!this.mapService.isWalkable(game.map, x, y) ||
			this.getBombAt(game, x, y)
		) {
			return undefined;
		}

		const bomb = new Bomb(
			playerId,
			x,
			y,
			bombRange,
			damage,
			explosionDelay,
		);

		game.bombs.set(bomb.id, bomb);
		player.availableBombs--;
		player.stats.bombsPlaced++;

		return bomb;
	}


	getBomb(
		game: GameState,
		id: string,
	): Bomb | undefined {
		return game.bombs.get(id);
	}


	getBombAt(
		game: GameState,
		x: number,
		y: number,
	): Bomb | undefined {
		return this.getBombs(game).find(
			(bomb) => bomb.x === x && bomb.y === y,
		);
	}


	removeBomb(
		game: GameState,
		id: string,
	): boolean {
		return game.bombs.delete(id);
	}


	hasBomb(
		game: GameState,
		id: string,
	): boolean {
		return game.bombs.has(id);
	}


	getBombs(game: GameState): Bomb[] {
		return Array.from(game.bombs.values());
	}


	getPlayerBombs(
		game: GameState,
		playerId: number,
	): Bomb[] {
		return this.getBombs(game).filter(
			(bomb) => bomb.playerId === playerId,
		);
	}


	getBombsToExplode(game: GameState): Bomb[] {
		return this.getBombs(game).filter(
			(bomb) => bomb.shouldExplode(),
		);
	}


	explodeBomb(
		game: GameState,
		//state: GameState,
		id: string,
	): ExplosionResult | undefined {
		const bomb = this.getBomb(game, id);

		if (!bomb || bomb.hasExploded()) {
			return undefined;
		}

		const result: ExplosionResult = {
			gameId: game.gameId,
			bombId: bomb.id,
			playerId: bomb.playerId,
			explosions: [],
			destroyedBlocks: [],
			powerUps: [],
			spawnedPowerUps: [],
			hitPlayers: [],
			deadPlayers: [],
			chainReactionBombIds: [],
		};

		this.resolveExplosion(game, bomb.id, result, false);
		return result;
	}


	private resolveExplosion(
		
		game: GameState,
		id: string,
		result: ExplosionResult,
		chainReaction: boolean,
	): void {
		const bomb = this.getBomb(game, id);

		if (!bomb || bomb.hasExploded()) {
			return;
		}

		bomb.explode();
		this.removeBomb(game, bomb.id);

		if (chainReaction) {
			result.chainReactionBombIds.push(bomb.id);
		}

		const owner = this.playerService.getPlayer(game, bomb.playerId);
		if (owner) {
			owner.availableBombs = Math.min(
				owner.availableBombs + 1,
				owner.maxBombs,
			);
		}

		const explosion: ExplosionData = {
			bombId: bomb.id,
			playerId: bomb.playerId,
			center: {
				x: bomb.x,
				y: bomb.y,
			},
			cells: [],
		};

		result.explosions.push(explosion);

		this.damagePlayersAt(
			game,
			bomb.x,
			bomb.y,
			bomb.damage,
			result,
		);

		const directions = [
			{ dx: 0, dy: -1 },
			{ dx: 0, dy: 1 },
			{ dx: -1, dy: 0 },
			{ dx: 1, dy: 0 },
		];

		for (const direction of directions) {
			this.calculateExplosionDirection(
				game,
				bomb,
				direction.dx,
				direction.dy,
				result,
				explosion,
			);
		}
	}


	private calculateExplosionDirection(
		game: GameState,
		bomb: Bomb,
		dx: number,
		dy: number,
		result: ExplosionResult,
		explosion: ExplosionData
	): void {
		for (let distance = 1; distance <= bomb.range; distance++) {
			const x = bomb.x + dx * distance;
			const y = bomb.y + dy * distance;

			if (!this.mapService.isInside(game.map, x, y)) {
				break;
			}

			if (this.mapService.isHardBlock(game.map, x, y)) {
				break;
			}

			this.addCell(explosion.cells, x, y);
			this.damagePlayersAt(game, x, y, bomb.damage, result);

			const chainedBomb = this.getBombAt(game, x, y);
			if (chainedBomb) {
				this.resolveExplosion(game, chainedBomb.id, result, true);
			}

			if (!this.mapService.isFragileBlock(game.map, x, y)) {
				continue;
			}

			this.mapService.destroyFragileBlock(game.map, x, y);
			result.destroyedBlocks.push({ x, y });

			const owner = this.playerService.getPlayer(game, bomb.playerId);
			if (owner) {
				owner.stats.blocksDestroyed++;
			}

			const powerUp = this.powerUpService.trySpawnPowerUp(game, x, y);
			if (powerUp) {
				const powerUpDto = {
					id: powerUp.id,
					type: powerUp.type,
					x: powerUp.x,
					y: powerUp.y,
				};
				result.powerUps.push(powerUpDto);
				result.spawnedPowerUps.push(powerUpDto);
			}

			break;
		}
	}


	private damagePlayersAt(
		game: GameState,
		//state: GameState,
		x: number,
		y: number,
		damage: number,
		result: ExplosionResult,
	): void {
		for (const player of this.playerService.getPlayers(game)) {
			if (
				!player.alive ||
				player.x !== x ||
				player.y !== y
			) {
				continue;
			}

			player.health -= damage;

			if (player.health <= 0) {
				player.health = 0;
				player.alive = false;

				if (!result.deadPlayers.includes(player.id)) {
					result.deadPlayers.push(player.id);
				}

				const killer = this.playerService.getPlayer(game, result.playerId);

				if (killer && killer.id !== player.id) {
					killer.stats.kills++;
				}
			}

			if (!result.hitPlayers.includes(player.id)) {
				result.hitPlayers.push(player.id);
			}
		}
	}


	private addCell(
		cells: ExplosionCell[],
		x: number,
		y: number,
	): void {
		if (!cells.some((cell) => cell.x === x && cell.y === y)) {
			cells.push({ x, y });
		}
	}
}