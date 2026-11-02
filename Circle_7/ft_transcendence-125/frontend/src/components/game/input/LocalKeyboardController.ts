/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  LocalKeyboardController.ts                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 11:09:47 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/26 22:26:44 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import type { PlayerController, Direction } from './PlayerController';

export type KeyBinding = 'wasd' | 'arrows';

export class LocalKeyboardController implements PlayerController {
	private keys: Record<'up' | 'down' | 'left' | 'right', Phaser.Input.Keyboard.Key>;
	private bombKey: Phaser.Input.Keyboard.Key;

	constructor(scene: Phaser.Scene, binding: KeyBinding) {
		const keyboard = scene.input.keyboard!;
		this.keys = binding === 'wasd'
			? {
				up: keyboard.addKey('W'),
				down: keyboard.addKey('S'),
				left: keyboard.addKey('A'),
				right: keyboard.addKey('D'),
			  }
			: {
				up: keyboard.addKey('UP'),
				down: keyboard.addKey('DOWN'),
				left: keyboard.addKey('LEFT'),
				right: keyboard.addKey('RIGHT'),
			  };

		this.bombKey = binding === 'wasd'
			? keyboard.addKey('SPACE')
			: keyboard.addKey('NUMPAD_ZERO');

		const allKeys = [...Object.values(this.keys), this.bombKey];
		keyboard.addCapture(allKeys.map((key) => key.keyCode));
	}

	getDirection(): Direction {
		let dirX = 0;
		let dirY = 0;

		if (this.keys.left.isDown) dirX -= 1;
		if (this.keys.right.isDown) dirX += 1;
		if (this.keys.up.isDown) dirY -= 1;
		if (this.keys.down.isDown) dirY += 1;

		return { dirX, dirY };
	}

	isMovementJustPressed(): boolean {
		return Object.values(this.keys).some((key) =>
			Phaser.Input.Keyboard.JustDown(key)
		);
	}

	isMovementJustReleased(): boolean {
		return Object.values(this.keys).some((key) =>
			Phaser.Input.Keyboard.JustUp(key)
		);
	}

	isBombKeyJustPressed(): boolean {
		return Phaser.Input.Keyboard.JustDown(this.bombKey);
	}
}
