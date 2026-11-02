/* ************************************************************************** */
/*                            TMP TEST FILE                                   */
/* ************************************************************************** */

import type { GameApi, WallData, ItemData } from '../api/GameApi';
import { cellKey } from '../config/gridConfig';
import { debugLog } from '../config/debugConfig';

const WALL_TEST_CELLS: { col: number; row: number }[] = [
	{ col: 2, row: 2 },
	{ col: 4, row: 3 },
	{ col: 6, row: 5 },
	{ col: 8, row: 4 },
	{ col: 10, row: 2 },
];
const WALL_TEST_DATA: WallData[] = WALL_TEST_CELLS.map(({ col, row }) => ({
	id: cellKey(col, row),
	col,
	row,
}));

const ITEM_TEST_DATA: ItemData[] = [
	{ id: 'i1', type: 'bomb-up',    col: 3,  row: 2 },
	{ id: 'i2', type: 'power-up',   col: 6,  row: 3 },
	{ id: 'i3', type: 'speed-down', col: 8,  row: 3 },
	{ id: 'i4', type: 'kick',       col: 11, row: 2 },
	{ id: 'i5', type: 'bomb-down',  col: 4,  row: 4 },
	{ id: 'i6', type: 'power-down', col: 2,  row: 6 },
	{ id: 'i7', type: 'speed-up',   col: 10, row: 5 },
];

export function spawnTestFixtures(api: GameApi) {
	api.syncWalls(WALL_TEST_DATA);
	api.syncItems(ITEM_TEST_DATA);
	debugLog('[TEST FIXTURES] spawned via GameApi');
}
