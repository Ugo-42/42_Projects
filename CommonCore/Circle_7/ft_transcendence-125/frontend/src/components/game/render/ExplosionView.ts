/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  ExplosionView.ts                                       ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/28 18:07:24 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/10 14:30:31 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { ExplosionPieceView } from './ExplosionPieceView';
import { DIRECTION_TRANSFORM } from '../config/explosionConfig';
import type { Direction } from '../config/explosionConfig';
import { cellToWorld } from '../config/gridConfig';

export interface ExplosionHitCell {
	col: number;
	row: number;
	kind: 'side' | 'tip';
}

function directionOf(centerCol: number, centerRow: number, cell: { col: number; row: number }): Direction {
	if (cell.row === centerRow) return cell.col > centerCol ? 'right' : 'left';
	return cell.row > centerRow ? 'down' : 'up';
}

export class ExplosionView {
	private pieces: ExplosionPieceView[] = [];
	private pendingCount: number;

	constructor(
		scene: Phaser.Scene,
		centerCol: number,
		centerRow: number,
		hitCells: ExplosionHitCell[],
		onComplete: () => void,
	) {
		this.pendingCount = 1 + hitCells.length;
		const onPieceComplete = () => {
			this.pendingCount -= 1;
			if (this.pendingCount === 0) onComplete();
		};

		const center = cellToWorld(centerCol, centerRow);
		this.pieces.push(new ExplosionPieceView(scene, 'center', center.x, center.y, 0, false, onPieceComplete));

		hitCells.forEach((cell) => {
			const direction = directionOf(centerCol, centerRow, cell);
			const { angle, flipX } = DIRECTION_TRANSFORM[direction];
			const { x, y } = cellToWorld(cell.col, cell.row);
			this.pieces.push(new ExplosionPieceView(scene, cell.kind, x, y, angle, flipX, onPieceComplete));
		});
	}

	destroy() {
		this.pieces.forEach((piece) => piece.destroy());
		this.pieces = [];
	}
}
