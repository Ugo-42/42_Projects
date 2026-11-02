/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  ExplosionPieceView.ts                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/28 18:05:58 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/28 18:07:00 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { SCALE, worldToScreen } from '../config/screenConfig';
import { EXPLOSION_DURATION_MS } from '../config/explosionConfig';

const TOTAL_FRAMES = 25;

export type ExplosionPieceKind = 'center' | 'side' | 'tip';

const ANIM_KEYS: Record<ExplosionPieceKind, string> = {
	center: 'explosion-center',
	side: 'explosion-side',
	tip: 'explosion-tip',
};

const TEXTURE_KEYS: Record<ExplosionPieceKind, string> = {
	center: 'bbm-explosion-center',
	side: 'bbm-explosion-side',
	tip: 'bbm-explosion-tip',
};

export class ExplosionPieceView {
	private sprite: Phaser.GameObjects.Sprite;

	static registerAnimations(scene: Phaser.Scene) {
		(Object.keys(ANIM_KEYS) as ExplosionPieceKind[]).forEach((kind) => {
			const key = ANIM_KEYS[kind];
			if (scene.anims.exists(key)) return;
			scene.anims.create({
				key,
				frames: scene.anims.generateFrameNumbers(TEXTURE_KEYS[kind], { start: 0, end: TOTAL_FRAMES - 1 }),
				frameRate: TOTAL_FRAMES / (EXPLOSION_DURATION_MS / 1000),
				repeat: 0,
			});
		});
	}

	constructor(
		scene: Phaser.Scene,
		kind: ExplosionPieceKind,
		worldX: number,
		worldY: number,
		angle: number,
		flipX: boolean,
		onComplete: () => void,
	) {
		const screen = worldToScreen(worldX, worldY);
		this.sprite = scene.add.sprite(screen.x, screen.y, TEXTURE_KEYS[kind], 0).setScale(SCALE);
		this.sprite.setAngle(angle);
		this.sprite.setFlipX(flipX);

		this.sprite.play(ANIM_KEYS[kind]);
		this.sprite.once('animationcomplete', () => {
			this.destroy();
			onComplete();
		});
	}

	destroy() {
		this.sprite.destroy();
	}
}
