/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  PlayerController.ts                                    ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 11:09:26 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/26 22:24:58 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export interface Direction {
	dirX: number;
	dirY: number;
}

export interface PlayerController {
	getDirection(): Direction;
	isBombKeyJustPressed(): boolean;
}
