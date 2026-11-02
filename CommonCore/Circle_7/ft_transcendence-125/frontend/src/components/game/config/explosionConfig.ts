/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  explosionConfig.ts                                     ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/28 18:04:39 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/12 13:58:07 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export const EXPLOSION_DURATION_MS = 450;

export type Direction = 'up' | 'down' | 'left' | 'right';

export const DIRECTION_VECTORS: Record<Direction, { dx: number; dy: number }> = {
	up:    { dx: 0,  dy: -1 },
	down:  { dx: 0,  dy: 1  },
	left:  { dx: -1, dy: 0  },
	right: { dx: 1,  dy: 0  },
};

export const DIRECTION_TRANSFORM: Record<Direction, { angle: number; flipX: boolean }> = {
	up:    { angle: 90,  flipX: false },
	down:  { angle: -90, flipX: false },
	left:  { angle: 0,   flipX: false },
	right: { angle: 0,   flipX: true  },
};
