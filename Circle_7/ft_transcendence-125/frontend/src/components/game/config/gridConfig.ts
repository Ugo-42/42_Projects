/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  gridConfig.ts                                          ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/30 00:21:06 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/30 00:21:08 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export const CELL_SIZE = 144;
export const GRID_ORIGIN_X = 842;
export const GRID_ORIGIN_Y = 432;

export function worldToCell(x: number, y: number) {
	return {
		col: Math.floor((x - GRID_ORIGIN_X) / CELL_SIZE),
		row: Math.floor((y - GRID_ORIGIN_Y) / CELL_SIZE),
	};
}

export function cellToWorld(col: number, row: number) {
	return {
		x: GRID_ORIGIN_X + col * CELL_SIZE + CELL_SIZE / 2,
		y: GRID_ORIGIN_Y + row * CELL_SIZE + CELL_SIZE / 2,
	};
}

export function snapToGridCenter(x: number, y: number) {
	const { col, row } = worldToCell(x, y);
	return cellToWorld(col, row);
}

export function cellKey(col: number, row: number) {
	return `${col},${row}`;
}
