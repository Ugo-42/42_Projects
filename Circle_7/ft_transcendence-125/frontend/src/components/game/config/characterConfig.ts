/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  characterConfig.ts                                     ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/09/11 15:54:02 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/12 13:31:58 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export const CHARACTER_FRAME_SIZE = 144;
export const CHARACTER_WALK_FRAMES = 8;
export const CHARACTER_WALK_CYCLE_MS = 500;

export type FacingDirection = 'up' | 'down' | 'left' | 'right';

export const DIRECTION_ROW: Record<FacingDirection, number> = {
	right: 0,
	down: 1,
	left: 2,
	up: 3,
};

export type CharacterColor =
	| 'blue' | 'cyan' | 'green' | 'orange'
	| 'pink' | 'purple' | 'red' | 'yellow';

export function characterTextureKey(color: CharacterColor): string {
	return `bbm-player-${color}`;
}
