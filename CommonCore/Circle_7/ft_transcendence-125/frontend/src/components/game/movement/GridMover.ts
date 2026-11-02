/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  GridMover.ts                                           ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/09/12 00:04:07 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/14 15:24:46 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export interface Direction {
	dirX: number;
	dirY: number;
}

export type IsBlockedFn = (col: number, row: number) => boolean;

const MAX_SEGMENTS_PER_FRAME = 8;

export class GridMover {
	private col: number;
	private row: number;
	private target: { col: number; row: number } | null = null;
	private progress = 0;
	private cellsPerSecond: number;

	constructor(startCol: number, startRow: number, cellsPerSecond: number) {
		this.col = startCol;
		this.row = startRow;
		this.cellsPerSecond = cellsPerSecond;
	}

	private discretize(direction: Direction): { dx: number; dy: number } {
		const dx = direction.dirX !== 0 ? Math.sign(direction.dirX) : 0;
		const dy = dx === 0 && direction.dirY !== 0 ? Math.sign(direction.dirY) : 0;
		return { dx, dy };
	}

	update(direction: Direction, dt: number, isBlocked: IsBlockedFn): { col: number; row: number } {
		let remaining = this.cellsPerSecond * dt;
		let segments = 0;

		while (remaining > 0 && segments < MAX_SEGMENTS_PER_FRAME) {
			segments++;

			if (!this.target) {
				const { dx, dy } = this.discretize(direction);
				if (dx === 0 && dy === 0) break;

				const nextCol = this.col + dx;
				const nextRow = this.row + dy;
				if (isBlocked(nextCol, nextRow)) break;

				this.target = { col: nextCol, row: nextRow };
				this.progress = 0;
			}

			const distanceLeftInSegment = 1 - this.progress;
			if (remaining < distanceLeftInSegment) {
				this.progress += remaining;
				remaining = 0;
			} else {
				remaining -= distanceLeftInSegment;
				this.col = this.target.col;
				this.row = this.target.row;
				this.target = null;
				this.progress = 0;
			}
		}

		if (!this.target) {
			return { col: this.col, row: this.row };
		}

		return {
			col: this.col + (this.target.col - this.col) * this.progress,
			row: this.row + (this.target.row - this.row) * this.progress,
		};
	}

	getNearestCell(): { col: number; row: number } {
		if (!this.target) return { col: this.col, row: this.row };
		return {
			col: Math.round(this.col + (this.target.col - this.col) * this.progress),
			row: Math.round(this.row + (this.target.row - this.row) * this.progress),
		};
	}
}
