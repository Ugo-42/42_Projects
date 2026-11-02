/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  BombView.ts                                            ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/26 22:25:17 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/26 22:25:53 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { SCALE, worldToScreen } from '../config/screenConfig';

const BOMB_ANIM_KEY = 'bomb-lifecycle';
const BOMB_DURATION_MS = 2500;
const TOTAL_FRAMES = 25;

export class BombView {
	private sprite: Phaser.GameObjects.Sprite;

	static registerAnimations(scene: Phaser.Scene) {
		if (scene.anims.exists(BOMB_ANIM_KEY)) return;

		scene.anims.create({
			key: BOMB_ANIM_KEY,
			frames: scene.anims.generateFrameNumbers('bbm-bomb', { start: 0, end: TOTAL_FRAMES - 1 }),
			frameRate: TOTAL_FRAMES / (BOMB_DURATION_MS / 1000),
			repeat: 0,
		});
	}

	constructor(scene: Phaser.Scene, worldX: number, worldY: number, onComplete: () => void) {
		const screen = worldToScreen(worldX, worldY);
		this.sprite = scene.add.sprite(screen.x, screen.y, 'bbm-bomb', 0).setScale(SCALE);

		this.sprite.play(BOMB_ANIM_KEY);
		this.sprite.once('animationcomplete', () => {
			this.destroy();
			onComplete();
		});
	}

	moveTo(
		worldX: number,
		worldY: number,
	): void {
		const screen = worldToScreen(worldX, worldY)
		this.sprite.setPosition(screen.x, screen.y)
	}

	destroy() {
		this.sprite.destroy();
	}
}
