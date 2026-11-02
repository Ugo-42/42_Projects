/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  debugConfig.ts                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 11:00:17 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/24 11:00:20 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export const DEBUG = true;

export function debugLog(...args: unknown[]) {
	if (DEBUG) console.log(...args);
}
