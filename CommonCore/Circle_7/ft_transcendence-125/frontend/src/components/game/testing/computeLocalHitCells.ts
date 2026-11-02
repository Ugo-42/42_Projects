/* ************************************************************************** */
/*                            TMP TEST FILE                                   */
/* ************************************************************************** */

import type { ExplosionHitCell } from '../render/ExplosionView';
import { DIRECTION_VECTORS } from '../config/explosionConfig';
import type { Direction } from '../config/explosionConfig';
import { isSolidWallAt } from '../config/solidWalls';

const DIRECTIONS: Direction[] = ['up', 'down', 'left', 'right'];

export interface LocalExplosionResult {
	hitCells: ExplosionHitCell[];
	destroyedWallIds: string[];
}

export function computeLocalHitCells(
	centerCol: number,
	centerRow: number,
	power: number,
	hasDestructibleWallAt: (col: number, row: number) => string | null,
): LocalExplosionResult {
	const hitCells: ExplosionHitCell[] = [];
	const destroyedWallIds: string[] = [];

	DIRECTIONS.forEach((direction) => {
		const { dx, dy } = DIRECTION_VECTORS[direction];

		for (let i = 1; i <= power; i++) {
			const col = centerCol + dx * i;
			const row = centerRow + dy * i;

			if (isSolidWallAt(col, row)) break;

			const wallId = hasDestructibleWallAt(col, row);
			if (wallId) {
				hitCells.push({ col, row, kind: 'tip' });
				destroyedWallIds.push(wallId);
				break;
			}

			hitCells.push({ col, row, kind: i === power ? 'tip' : 'side' });
		}
	});

	return { hitCells, destroyedWallIds };
}
