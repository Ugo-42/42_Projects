import { PowerUpType } from './power-up';

export interface BombDto {
	id: string;
	playerId: number;
	x: number;
	y: number;
	range: number;
	damage: number;
	placedAt: number;
	explosionDelay: number;
}

export interface PowerUpDto {
	id: string;
	type: PowerUpType;
	x: number;
	y: number;
}