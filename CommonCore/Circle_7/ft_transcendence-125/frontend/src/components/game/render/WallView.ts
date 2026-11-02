/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  WallView.ts                                            ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/25 11:44:02 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/29 23:44:48 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { SCALE, worldToScreen } from '../config/screenConfig';

const BREAK_ANIM_KEY = 'wall-break';
const BREAK_DURATION_MS = 250;
const TOTAL_FRAMES = 25;

export class WallView {
	private sprite: Phaser.GameObjects.Sprite;

	static registerAnimations(scene: Phaser.Scene) {
		if (scene.anims.exists(BREAK_ANIM_KEY)) return;

		scene.anims.create({
			key: BREAK_ANIM_KEY,
			frames: scene.anims.generateFrameNumbers('bbm-wall-break', { start: 0, end: TOTAL_FRAMES - 1 }),
			frameRate: TOTAL_FRAMES / (BREAK_DURATION_MS / 1000),
			repeat: 0,
		});
	}

	constructor(scene: Phaser.Scene, worldX: number, worldY: number) {
		const screen = worldToScreen(worldX, worldY);
		this.sprite = scene.add.sprite(screen.x, screen.y, 'bbm-wall-break', 0).setScale(SCALE);
	}

	break(onComplete: () => void) {
		this.sprite.play(BREAK_ANIM_KEY);
		this.sprite.once('animationcomplete', () => {
			this.destroy();
			onComplete();
		});
	}

	destroy() {
		this.sprite.destroy();
	}
}
