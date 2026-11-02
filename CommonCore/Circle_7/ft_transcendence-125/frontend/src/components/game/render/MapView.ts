/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  MapView.ts                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/09/24 00:31:47 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/24 00:31:50 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { SCALE, worldToScreen } from '../config/screenConfig';
import { gridTextureKey } from '../config/themeConfig';
import type { ThemeName } from '../config/themeConfig';

export class MapView {
	private image: Phaser.GameObjects.Image;

	constructor(scene: Phaser.Scene, theme: ThemeName) {
		const { x, y } = worldToScreen(1920, 1080);
		this.image = scene.add.image(x, y, gridTextureKey(theme)).setScale(SCALE);
	}

	setTheme(theme: ThemeName): void {
		this.image.setTexture(gridTextureKey(theme));
	}

	destroy(): void {
		this.image.destroy();
	}
}
