/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  screenConfig.ts                                        ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 11:00:26 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/24 00:32:10 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export const SCALE = 1.35;
export const CENTER_X = 1920;
export const CENTER_Y = 1080;

export function worldToScreen(x: number, y: number) {
	return {
		x: CENTER_X + (x - CENTER_X) * SCALE,
		y: CENTER_Y + (y - CENTER_Y) * SCALE,
	};
}
