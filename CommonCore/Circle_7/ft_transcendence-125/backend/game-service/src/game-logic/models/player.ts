export enum PlayerColor {
	BLUE = 'blue',
	CYAN = 'cyan',
	GREEN = 'green',
	ORANGE = 'orange',
	YELLOW = 'yellow',
	RED = 'red',
	PINK = 'pink',
	PURPLE = 'purple',
}

export interface PlayerStats {
	kills: number;

	bombsPlaced: number;
	blocksDestroyed: number;

	powerUpsCollected: number;

	gamesWon: number;
}

export class Player {
	public readonly id: number;
	public readonly username: string;
	public readonly color: PlayerColor;

	public x: number;
	public y: number;

	// Statistiques de gameplay
	public speed: number = 1;
	public health: number = 1;
	public maxBombs: number = 1;
	public availableBombs: number = 1;
	public flameRange: number = 1;
	public canKickBombs: boolean = false;

	// État
	public alive: boolean = true;
	public ready: boolean = false;

	// Statistiques de la partie
	public stats: PlayerStats = {
		kills: 0,
		bombsPlaced: 0,
		blocksDestroyed: 0,
		powerUpsCollected: 0,
		gamesWon: 0,
	};

	constructor(
		id: number,
		username: string,
		color: PlayerColor,
		x: number,
		y: number,
	) {
		this.id = id;
		this.username = username;
		this.color = color;
		this.x = x;
		this.y = y;
	}
}

