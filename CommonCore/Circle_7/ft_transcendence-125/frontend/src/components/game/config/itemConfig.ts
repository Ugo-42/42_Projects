/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  itemConfig.ts                                          ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/26 10:13:22 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/28 12:36:40 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export type ItemType =
	| 'bomb-up' | 'bomb-down'
	| 'power-up' | 'power-down'
	| 'speed-up' | 'speed-down'
	| 'kick';

export const ITEM_TEXTURE_KEYS: Record<ItemType, string> = {
	'bomb-up': 'item-bomb-up',
	'bomb-down': 'item-bomb-down',
	'power-up': 'item-power-up',
	'power-down': 'item-power-down',
	'speed-up': 'item-speed-up',
	'speed-down': 'item-speed-down',
	'kick': 'item-kick',
};

export const ITEM_FLOAT_OFFSET = 10;
export const ITEM_FLOAT_DURATION_MS = 800;
export const ITEM_DISPLAY_SIZE = 144;

const POWERUP_TYPE_TO_ITEM_TYPE: Record<string, ItemType> = {
	bomb_plus: 'bomb-up',
	bomb_minus: 'bomb-down',
	kick: 'kick',
	speed_plus: 'speed-up',
	speed_minus: 'speed-down',
	flame_plus: 'power-up',
	flame_minus: 'power-down',
};

export function powerUpTypeToItemType(backendType: string): ItemType | null {
	return POWERUP_TYPE_TO_ITEM_TYPE[backendType] ?? null;
}
