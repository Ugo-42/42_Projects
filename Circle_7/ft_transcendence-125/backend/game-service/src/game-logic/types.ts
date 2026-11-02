import { BombDto, PowerUpDto } from './models/gameplay-dto';
import { TileType } from './models/map';

export interface Direction {
	dirX: number;
	dirY: number;
}

export enum GameStatus {
	RUNNING = 'running',
	ENDED = 'ended',
}

export interface PlayerStateDTO {
	id: number;
	username: string;
	color: string;
	x: number;
	y: number;
	alive: boolean;
	speed: number;
	maxBombs: number;
	availableBombs: number;
	flameRange: number;
	canKickBombs: boolean;
}

export interface MapDTO {
	cols: number;
	rows: number;
	tiles: TileType[][];
}

export interface GameStateDTO {
	gameId: string;
	status: GameStatus;
	map: MapDTO;
	players: PlayerStateDTO[];
	bombs: BombDto[];
	powerUps: PowerUpDto[];
	winnerId: number | null;
}

export interface ActionResult {
	success: boolean;
	reason?: string;
}
