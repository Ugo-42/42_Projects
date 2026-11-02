import { Bomb } from './bomb';
import { GameMap } from './map';
import { Player } from './player';
import { PowerUp } from './power-up';
import { GameStatus } from '../types';

export class GameState {
	public readonly players = new Map<number, Player>();
	public readonly bombs = new Map<string, Bomb>();
	public readonly powerUps = new Map<string, PowerUp>();
	public readonly createdAt: number = Date.now();
	public status: GameStatus = GameStatus.RUNNING;
	public winnerId: number | null = null;
	public endedAt: number | null = null;


	constructor(
		public readonly gameId: string,
		public readonly lobbyId: string,
		public readonly map: GameMap,
	) {}
}
