import { Injectable } from '@nestjs/common';

import {
	GameMap,
	TileType,
} from '../models/map';

@Injectable()
export class MapService {

	isInside(map: GameMap, x: number, y: number): boolean {
		return map.isInside(x, y);
	}

	getTile(map: GameMap, x: number, y: number): TileType | undefined {
		return map.getTile(x, y);
	}

	setTile(map: GameMap, x: number, y: number, type: TileType): boolean {
		return map.setTile(x, y, type);
	}

	isWalkable(map: GameMap, x: number, y: number): boolean {
		const tile = map.getTile(x, y);
		return (
			tile === TileType.EMPTY ||
			tile === TileType.SPAWN ||
			tile === TileType.PASSAGE
		);
	}

	isHardBlock(map: GameMap, x: number, y: number): boolean {
		return map.getTile(x, y) === TileType.HARD_BLOCK;
	}

	isFragileBlock(map: GameMap, x: number, y: number): boolean {
		return map.getTile(x, y) === TileType.FRAGILE_BLOCK;
	}

	destroyFragileBlock(map: GameMap, x: number, y: number): boolean {
		if (!this.isFragileBlock(map, x, y)) return false;
		map.setTile(x, y, TileType.EMPTY);
		return true;
	}

	generateFragileBlocks(map: GameMap, chance: number = 0): void {
		for (let y = 0; y < map.height; y++) {
			for (let x = 0; x < map.width; x++) {
				const tile = map.getTile(x, y);
				if (tile !== TileType.EMPTY) continue;
				if (Math.random() < chance) {
					map.setTile(x, y, TileType.FRAGILE_BLOCK);
				}
			}
		}
	}

	generateMap(
		spawnPoints: { x: number; y: number }[],
		cols: number = 15,
		rows: number = 9,
	): GameMap {
		const map = new GameMap(cols, rows);

		for (let y = 0; y < rows; y++) {
			for (let x = 0; x < cols; x++) {
				if (this.isPillarCell(x, y)) {
					map.setTile(x, y, TileType.HARD_BLOCK);
				} else if (this.isSpawnClearance(x, y, spawnPoints)) {
					map.setTile(x, y, TileType.SPAWN);
				}
			}
		}

		this.generateFragileBlocks(map, 0.8);
		return map;
	}

	getSpawnPoints(
		cols: number = 15,
		rows: number = 9,
		maxPlayers: number = 4,
	): { x: number; y: number }[] {
		const corners = [
			{ x: 0, y: 0 },
			{ x: cols - 1, y: 0 },
			{ x: 0, y: rows - 1 },
			{ x: cols - 1, y: rows - 1 },
		];
		return corners.slice(0, maxPlayers);
	}

	toGrid(map: GameMap): TileType[][] {
		const grid: TileType[][] = [];
		for (let y = 0; y < map.height; y++) {
			const row: TileType[] = [];
			for (let x = 0; x < map.width; x++) {
				row.push(map.getTile(x, y) ?? TileType.EMPTY);
			}
			grid.push(row);
		}
		return grid;
	}

	private isPillarCell(x: number, y: number): boolean {
		return y % 2 === 1 && x % 2 === 1;
	}

	private isSpawnClearance(x: number, y: number, spawnPoints: { x: number; y: number }[]): boolean {
		return spawnPoints.some((s) => Math.abs(s.x - x) + Math.abs(s.y - y) <= 1);
	}
}
