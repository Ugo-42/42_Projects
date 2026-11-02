/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  ItemView.ts                                            ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/26 10:13:46 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/26 13:27:03 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { SCALE, worldToScreen } from '../config/screenConfig';
import { ITEM_TEXTURE_KEYS, ITEM_DISPLAY_SIZE, ITEM_FLOAT_OFFSET, ITEM_FLOAT_DURATION_MS } from '../config/itemConfig';
import type { ItemType } from '../config/itemConfig';

export class ItemView {
	private sprite: Phaser.GameObjects.Image;
	private tween: Phaser.Tweens.Tween;

	constructor(scene: Phaser.Scene, type: ItemType, worldX: number, worldY: number) {
		const screen = worldToScreen(worldX, worldY);
		const displayPx = ITEM_DISPLAY_SIZE * SCALE;

		this.sprite = scene.add.image(screen.x, screen.y, ITEM_TEXTURE_KEYS[type]);
		this.sprite.setDisplaySize(displayPx, displayPx);

		this.tween = scene.tweens.add({
			targets: this.sprite,
			y: screen.y - ITEM_FLOAT_OFFSET * SCALE,
			duration: ITEM_FLOAT_DURATION_MS,
			ease: 'Sine.easeInOut',
			yoyo: true,
			repeat: -1,
		});
	}

	destroy() {
		this.tween.stop();
		this.sprite.destroy();
	}
}
