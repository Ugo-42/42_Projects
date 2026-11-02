/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  themeConfig.ts                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/09/24 00:31:21 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/24 00:40:19 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export type ThemeName = 'neon' | 'steampunk';

export const DEFAULT_THEME: ThemeName = 'neon';
export const THEME_NAMES: ThemeName[] = ['neon', 'steampunk'];

export function gridTextureKey(theme: ThemeName): string {
	return `bbm-grid-${theme}`;
}

