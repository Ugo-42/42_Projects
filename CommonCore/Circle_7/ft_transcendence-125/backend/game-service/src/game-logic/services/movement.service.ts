import { Injectable } from '@nestjs/common';
import { GameState } from '../models/game-state';
import { MapService } from './map.service';
import { BombService } from './bomb.service';
import type { Direction } from '../types';
import type { Bomb } from '../models/bomb';

const BASE_CELLS_PER_SECOND = 4;
const SPEED_LEVEL_BONUS = 1;

const MAX_STEPS_PER_TICK = 4;

@Injectable()
export class MovementService {
	constructor(
		private readonly bombService: BombService
	){}
	private progress = new Map<string, Map<number, number>>();

	private lastStepAt = new Map<string, Map<number, number>>();

	private getBucket(gameId: string): Map<number, number> {
		let bucket = this.progress.get(gameId);
		if (!bucket) {
			bucket = new Map();
			this.progress.set(gameId, bucket);
		}
		return bucket;
	}

	clearGame(gameId: string): void {
		this.progress.delete(gameId);
		this.lastStepAt.delete(gameId);
	}

	clearPlayer(gameId: string, playerId: number): void {
		this.progress.get(gameId)?.delete(playerId);
	}

	private getLastStepBucket(gameId: string): Map<number, number> {
		let bucket = this.lastStepAt.get(gameId);
		if (!bucket) {
			bucket = new Map();
			this.lastStepAt.set(gameId, bucket);
		}
		return bucket;
	}

	private getTimePerCell(state: GameState, playerId: number): number {
		const player = state.players.get(playerId);
		if (!player) return Infinity;
		const cellsPerSecond =
			BASE_CELLS_PER_SECOND +
			(player.speed - 1) * SPEED_LEVEL_BONUS;
		return 1000 / cellsPerSecond;
	}

	canStep(
		state: GameState,
		playerId: number,
	): boolean {
		const lastStep = this.getLastStepBucket(state.gameId).get(playerId);
		if (lastStep === undefined) return true;
		return Date.now() - lastStep >= this.getTimePerCell(state, playerId);
	}

	private tryMove(
		state: GameState,
		playerId: number,
		dx: number,
		dy: number,
		mapService: MapService,
	): boolean {
		const player = state.players.get(playerId);

		if (!player || !player.alive)
			return false;

		const nextX = player.x + dx;
		const nextY = player.y + dy;

		const bomb = this.bombService.getBombAt(
			state,
			nextX,
			nextY,
		);

		if (bomb) {
			if (!player.canKickBombs)
				return false;

			const bombNextX = nextX + dx;
			const bombNextY = nextY + dy;

			if (!this.isBombDestinationFree(
				state,
				bombNextX,
				bombNextY,
				mapService,
			)) {
				return false;
			}

			bomb.x = bombNextX;
			bomb.y = bombNextY;
		}
		else if (!this.isWalkable(state, nextX, nextY, mapService)) {
			return false;
		}

		player.x = nextX;
		player.y = nextY;

		return true;
	}

	step(
		state: GameState,
		playerId: number,
		direction: Direction,
		mapService: MapService,
	): boolean {
		const player = state.players.get(playerId);

		if (!player || !player.alive)
			return false;

		if (!this.canStep(state, playerId))
			return false;

		const { dx, dy } = this.discretize(direction);

		if (dx === 0 && dy === 0)
			return false;

		const moved = this.tryMove(
			state,
			playerId,
			dx,
			dy,
			mapService,
		);

		if (!moved) {
			this.getBucket(state.gameId).set(playerId, 0);
			return false;
		}

		this.getBucket(state.gameId).set(playerId, 0);
		this.getLastStepBucket(state.gameId).set(
			playerId,
			Date.now(),
		);

		return true;
	}

	advance(
		state: GameState,
		activeDirections: Map<number, Direction>,
		dt: number,
		mapService: MapService,
	): boolean {
		const bucket = this.getBucket(state.gameId)
		let moved = false
		activeDirections.forEach((direction, playerId) => {
			const player = state.players.get(playerId)
			if (!player || !player.alive) return
			const { dx, dy } = this.discretize(direction)
			if (dx === 0 && dy === 0) return
			const cellsPerSecond = BASE_CELLS_PER_SECOND + (player.speed - 1) * SPEED_LEVEL_BONUS
			const timePerCell = 1 / cellsPerSecond
			let elapsed = (bucket.get(playerId) ?? 0) + dt
			let steps = 0
			while (elapsed >= timePerCell && steps < MAX_STEPS_PER_TICK) {
				const movedThisStep = this.tryMove(
					state,
					playerId,
					dx,
					dy,
					mapService,
				);
				if (!movedThisStep) {
					elapsed = 0;
					break;
				}
				this.getLastStepBucket(state.gameId).set(
					playerId,
					Date.now(),
				);
				elapsed -= timePerCell;
				steps++;
				moved = true;
			}
			bucket.set(playerId, elapsed)
		})
		return moved
	}


	private discretize(
		direction: Direction,
	): { dx: number; dy: number } {
		const dx =
			direction.dirX !== 0
				? Math.sign(direction.dirX)
				: 0;

		const dy =
			dx === 0 && direction.dirY !== 0
				? Math.sign(direction.dirY)
				: 0;

		return { dx, dy };
	}

	private isBombDestinationFree(
		state: GameState,
		x: number,
		y: number,
		mapService: MapService,
	): boolean {
		if (!mapService.isInside(state.map, x, y))
			return false;

		if (!mapService.isWalkable(state.map, x, y))
			return false;

		if (this.bombService.getBombAt(state, x, y))
			return false;

		return true;
	}

	private isWalkable(
		state: GameState,
		x: number,
		y: number,
		mapService: MapService,
	): boolean {
		if (!mapService.isInside(state.map, x, y))
			return false;
		if (mapService.isHardBlock(state.map, x, y))
			return false;
		if (mapService.isFragileBlock(state.map, x, y))
			return false;
		if (this.bombService.getBombAt(state, x, y))
			return false;

		return true;
	}
}