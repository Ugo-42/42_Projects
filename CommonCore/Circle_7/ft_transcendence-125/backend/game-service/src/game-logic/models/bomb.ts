export class Bomb {
	public readonly id: string;
	public readonly playerId: number;
	public x: number;
	public y: number;
	public readonly damage: number;
	public readonly range: number;
	public readonly createdAt: number;
	public readonly explosionDelay: number;
	private exploded: boolean = false;

	constructor(
		playerId: number,
		x: number,
		y: number,
		range: number = 1,
		damage: number = 1,
		explosionDelay: number = 2500,
	) {
		this.id = crypto.randomUUID();
		this.playerId = playerId;
		this.x = x;
		this.y = y;
		this.range = range;
		this.damage = damage;
		this.createdAt = Date.now();
		this.explosionDelay = explosionDelay;
	}

	// verifie si la bombe doit exploser
	shouldExplode(): boolean {
		return (!this.exploded && Date.now() - this.createdAt >= this.explosionDelay);
	}

	//marque la bombe comme explosee
	explode(): void {
		this.exploded = true;
	}

	// verifie si la bombe a deja explose
	hasExploded(): boolean {
		return this.exploded;
	}
}