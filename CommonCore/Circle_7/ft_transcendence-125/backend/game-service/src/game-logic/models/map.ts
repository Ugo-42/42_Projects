export enum TileType {
	EMPTY = 'empty',
	HARD_BLOCK = 'hard_block',
	FRAGILE_BLOCK = 'fragile_block',
	SPAWN = 'spawn',
	PASSAGE = 'passage',
}

export class GameMap {
	public readonly width: number;
	public readonly height: number;

	private readonly tiles: TileType[][];

	constructor(
		width: number,
		height: number,
	) {
		this.width = width;
		this.height = height;

		this.tiles = Array.from(
			{ length: height },
			() =>
				Array.from(
					{ length: width },
					() => TileType.EMPTY,
				),
		);
	}

	getTile(
		x: number,
		y: number,
	): TileType | undefined {
		if (!this.isInside(x, y)) {
			return undefined;
		}

		return this.tiles[y][x];
	}

	setTile(
		x: number,
		y: number,
		type: TileType,
	): boolean {
		if (!this.isInside(x, y)) {
			return false;
		}

		this.tiles[y][x] = type;

		return true;
	}

	isInside(
		x: number,
		y: number,
	): boolean {
		return (
			x >= 0 &&
			x < this.width &&
			y >= 0 &&
			y < this.height
		);
	}
}