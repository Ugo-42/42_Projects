export enum PowerUpType {
	BOMB_PLUS = 'bomb_plus',
	BOMB_MINUS = 'bomb_minus',

	KICK = 'kick',

	SPEED_PLUS = 'speed_plus',
	SPEED_MINUS = 'speed_minus',

	FLAME_PLUS = 'flame_plus',
	FLAME_MINUS = 'flame_minus',
}

export class PowerUp {
	public readonly id: string;
	public readonly type: PowerUpType;
	public readonly x: number;
	public readonly	y: number;
	private collected: boolean = false;

	constructor(
		type: PowerUpType,
		x: number,
		y: number,
	) {
		this.id = crypto.randomUUID();
		this.type = type;
		this.x = x;
		this.y = y;
	}

	collect(): void {
		this.collected = true;
	}

	isCollected(): boolean {
		return this.collected;
	}
}

