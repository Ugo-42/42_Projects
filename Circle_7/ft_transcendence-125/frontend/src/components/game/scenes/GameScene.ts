/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  GameScene.ts                                           ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 11:00:38 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/01 13:44:56 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';

import { DEATH_TEXTURE_KEY } from '../config/deathConfig';
import { THEME_NAMES, gridTextureKey } from '../config/themeConfig';
import { BombView }                    from '../render/BombView';
import { ExplosionPieceView }          from '../render/ExplosionPieceView';
import { GameApi }                     from '../api/GameApi';
import { ITEM_TEXTURE_KEYS }           from '../config/itemConfig';
import { LocalKeyboardController }     from '../input/LocalKeyboardController';
import { PlayerView }                  from '../render/PlayerView';
import { WallView }                    from '../render/WallView';
import { characterTextureKey }         from '../config/characterConfig';
import { RemoteGameClient }            from '../client/RemoteGameClient';

import type { ItemType }       from '../config/itemConfig';
import type { ThemeName }      from '../config/themeConfig';
import type { CharacterColor } from '../config/characterConfig';
import type { GameEndedPayload } from "@/services/gameSocketService"

import bbmDeath           from '../assets/bbm_death.png';
import neonGrid           from '../assets/map/neon/bbm_grid.png';
import steampunkGrid      from '../assets/map/steampunk/bbm_grid.png';
import bbmBombAnim        from '../assets/bbm_bomb.png';
import bbmExplosionCenter from '../assets/bbm_explosion_center.png';
import bbmExplosionSide   from '../assets/bbm_explosion_side.png';
import bbmExplosionTip    from '../assets/bbm_explosion_tip.png';
import bbmWallAnim        from '../assets/bbm_wall.png';
import charBlue           from '../assets/character/bbm_player_blue.png';
import charCyan           from '../assets/character/bbm_player_cyan.png';
import charGreen          from '../assets/character/bbm_player_green.png';
import charOrange         from '../assets/character/bbm_player_orange.png';
import charPink           from '../assets/character/bbm_player_pink.png';
import charPurple         from '../assets/character/bbm_player_purple.png';
import charRed            from '../assets/character/bbm_player_red.png';
import charYellow         from '../assets/character/bbm_player_yellow.png';
import itemBombDown       from '../assets/bbm_bomb_down.png';
import itemBombUp         from '../assets/bbm_bomb_up.png';
import itemKick           from '../assets/bbm_kick.png';
import itemPowerDown      from '../assets/bbm_power_down.png';
import itemPowerUp        from '../assets/bbm_power_up.png';
import itemSpeedDown      from '../assets/bbm_speed_down.png';
import itemSpeedUp        from '../assets/bbm_speed_up.png';


const THEME_GRID_ASSETS: Record<ThemeName, string> = {
	neon: neonGrid,
	steampunk: steampunkGrid,
};

const CHARACTER_ASSETS: Record<CharacterColor, string> = {
	blue: charBlue,
	cyan: charCyan,
	green: charGreen,
	orange: charOrange,
	pink: charPink,
	purple: charPurple,
	red: charRed,
	yellow: charYellow,
};

export class GameScene extends Phaser.Scene {
	private controller!: LocalKeyboardController;
	private api!: GameApi;
	private remoteGameClient: RemoteGameClient | null = null;
	private lastDirection = { dirX: 0, dirY: 0 }
	private bombKey?: Phaser.Input.Keyboard.Key
	private onGameEnded?: (
		winnerId: number | null,
		winnerName: string | null,
		data: GameEndedPayload
	) => void;


	constructor(
		onGameEnded?: (
			winnerId: number | null,
			winnerName: string | null,
			data: GameEndedPayload
		) => void,
	) {
		super("GameScene")
		this.onGameEnded = onGameEnded
	}

	preload() {
		this.load.spritesheet('bbm-wall-break', bbmWallAnim, { frameWidth: 144, frameHeight: 144 });
		this.load.spritesheet('bbm-bomb', bbmBombAnim, { frameWidth: 144, frameHeight: 144 });
		this.load.spritesheet('bbm-explosion-center', bbmExplosionCenter, { frameWidth: 144, frameHeight: 144 });
		this.load.spritesheet('bbm-explosion-side', bbmExplosionSide, { frameWidth: 144, frameHeight: 144 });
		this.load.spritesheet('bbm-explosion-tip', bbmExplosionTip, { frameWidth: 144, frameHeight: 144 });
		this.load.spritesheet(DEATH_TEXTURE_KEY, bbmDeath, { frameWidth: 144, frameHeight: 144 });

		THEME_NAMES.forEach((theme) => {
			this.load.image(gridTextureKey(theme), THEME_GRID_ASSETS[theme]);
		});

		Object.entries(CHARACTER_ASSETS).forEach(([color, path]) => {
			this.load.spritesheet(characterTextureKey(color as CharacterColor), path, {
				frameWidth: 144,
				frameHeight: 144,
			});
		});

		const itemAssets: Record<ItemType, string> = {
			'bomb-up': itemBombUp,
			'bomb-down': itemBombDown,
			'power-up': itemPowerUp,
			'power-down': itemPowerDown,
			'speed-up': itemSpeedUp,
			'speed-down': itemSpeedDown,
			'kick': itemKick,
		};

		Object.entries(itemAssets).forEach(([type, path]) => {
			this.load.image(ITEM_TEXTURE_KEYS[type as ItemType], path);
		});

		this.load.on('loaderror', (file: { key: string; src: string }) => {
			console.error('[LOAD ERROR]', file.key, file.src);
		});
	}

	create() {
		this.onGameEnded = this.registry.get('onGameEnded')
		WallView.registerAnimations(this);
		BombView.registerAnimations(this);
		PlayerView.registerDeathAnimation(this);
		ExplosionPieceView.registerAnimations(this);
		const characterColors: CharacterColor[] = [
			'blue', 'cyan', 'green', 'orange', 'pink', 'purple', 'red', 'yellow'
		];
		characterColors.forEach((color) => {
			PlayerView.registerAnimations(this, characterTextureKey(color))});

		this.controller = new LocalKeyboardController(this, 'wasd');

		this.api = new GameApi(this);
		this.api.initMap();


		const gameId = sessionStorage.getItem("currentGameId");

		if (!gameId) {
			console.error("[GAME] Missing currentGameId");
			return;
		}

		this.remoteGameClient = new RemoteGameClient(gameId, this.api,
			(winnerId, winnerName, data) => {
				this.remoteGameClient?.destroy()
				this.remoteGameClient = null
				this.onGameEnded?.(winnerId, winnerName, data)
		});

		this.events.once(Phaser.Scenes.Events.SHUTDOWN, () => {
			this.remoteGameClient?.sendStop();
			this.remoteGameClient?.destroy();
			this.remoteGameClient = null;
		});
		this.bombKey = this.input.keyboard?.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE)
	}

	update(_time: number, delta: number) {
		this.api.updatePlayers(delta)
		if (this.bombKey && Phaser.Input.Keyboard.JustDown(this.bombKey)) {
			this.remoteGameClient?.sendBombPlace()
		}
		const direction = this.controller.getDirection()
		const changed = direction.dirX !== this.lastDirection.dirX || direction.dirY !== this.lastDirection.dirY

		if (!changed) return

		this.lastDirection = direction

		if (direction.dirX === 0 && direction.dirY === 0) {
			this.remoteGameClient?.sendStop()
			return
		}

		this.remoteGameClient?.sendMove(direction.dirX, direction.dirY)
	}

}
