/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  themeManager.ts                                        ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/09/24 00:30:57 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/24 00:31:08 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import type { ThemeName } from '../config/themeConfig';
import { DEFAULT_THEME } from '../config/themeConfig';

type ThemeListener = (theme: ThemeName) => void;

class ThemeManager {
	private currentTheme: ThemeName = DEFAULT_THEME;
	private listeners = new Set<ThemeListener>();

	getTheme(): ThemeName {
		return this.currentTheme;
	}

	setTheme(theme: ThemeName): void {
		if (theme === this.currentTheme) return;
		this.currentTheme = theme;
		this.listeners.forEach((notify) => notify(theme));
	}

	addThemeChangeListener(onThemeChange: ThemeListener): () => void {
		this.listeners.add(onThemeChange);
		return () => this.listeners.delete(onThemeChange);
	}
}

export const themeManager = new ThemeManager();

