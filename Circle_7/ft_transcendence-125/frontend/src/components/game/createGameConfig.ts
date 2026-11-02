/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  createGameConfig.ts                                    ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 10:59:56 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/01 13:39:21 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { GameScene } from './scenes/GameScene';
import type { GameEndedPayload } from "@/services/gameSocketService"

const WORLD_WIDTH = 3840;
const WORLD_HEIGHT = 2160;

export function createGameConfig(
	parent: HTMLElement,
	onGameEnded: (
		winnerId: number | null,
		winnerName: string | null,
		data: GameEndedPayload
	) => void,
): Phaser.Types.Core.GameConfig {
	return {
		type: Phaser.AUTO,
		parent,
		width: WORLD_WIDTH,
		height: WORLD_HEIGHT,
		transparent: true,
		scale: {
			mode: Phaser.Scale.FIT,
			autoCenter: Phaser.Scale.CENTER_BOTH,
		},
		scene: [GameScene],
		callbacks: {
			preBoot: (game) => {game.registry.set('onGameEnded', onGameEnded)}
		},
	};
}
