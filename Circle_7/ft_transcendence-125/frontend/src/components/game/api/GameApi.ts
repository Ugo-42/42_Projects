/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  GameApi.ts                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/09/10 14:26:47 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/30 20:58:40 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from 'phaser';
import { MapView } from '../render/MapView';
import { themeManager } from '../theme/themeManager';
import type { ThemeName } from '../config/themeConfig';
import { PlayerView } from '../render/PlayerView';
import { WallView } from '../render/WallView';
import { ItemView } from '../render/ItemView';
import { BombView } from '../render/BombView';
import { ExplosionView } from '../render/ExplosionView';
import type { ExplosionHitCell } from '../render/ExplosionView';
import { reconcileViews } from '../render/reconcileViews';
import type { Keyed } from '../render/reconcileViews';
import type { ItemType } from '../config/itemConfig';
import { cellToWorld, cellKey } from '../config/gridConfig';
import { debugLog } from '../config/debugConfig';

export interface WallData extends Keyed { col: number; row: number }
export interface ItemData extends Keyed { type: ItemType; col: number; row: number }

export class GameApi {
	private playerViews = new Map<string, PlayerView>();
	private wallViews = new Map<string, WallView>();
	private itemViews = new Map<string, ItemView>();
	private bombViews = new Map<string, BombView>();
	private mapView: MapView | null = null;
	private scene: Phaser.Scene;

	constructor(scene: Phaser.Scene) {
		this.scene = scene;
	}


	/* --- Map / Theme --- */

	initMap(theme: ThemeName = themeManager.getTheme()): void {
		this.mapView = new MapView(this.scene, theme);

		themeManager.addThemeChangeListener((newTheme) => {
			this.mapView?.setTheme(newTheme);
		});
	}

	setTheme(theme: ThemeName): void {
		themeManager.setTheme(theme);
	}


	/* --- Players --- */

	spawnPlayerAtWorld(id: string, characterKey: string, col: number, row: number): void {
		console.log("[GAME API] spawnPlayerAtWorld", {
			id,
			characterKey,
			col,
			row,
		})
		const { x, y } = cellToWorld(col, row)
		const view = new PlayerView(this.scene, characterKey);
		view.render(x, y);
		this.playerViews.set(id, view);
	}

	hasPlayer(id: string): boolean {
		return this.playerViews.has(id);
	}

	movePlayer(id: string, col: number, row: number): void {
		const { x, y } = cellToWorld(col, row);
		this.playerViews.get(id)?.render(x, y);
	}

	updatePlayers(delta: number): void {
		this.playerViews.forEach((view) => {
			view.update(delta)
		})
	}

	removePlayer(id: string): void {
		this.playerViews.get(id)?.destroy();
		this.playerViews.delete(id);
	}

	killPlayer(id: string, onComplete?: () => void): void {
		const view = this.playerViews.get(id);
		if (!view) return;

		view.playDeath(() => {
			this.playerViews.delete(id);
			onComplete?.();
		});
	}


	/* --- Walls --- */

	syncWalls(walls: WallData[]): void {
		reconcileViews(
			this.wallViews,
			walls,
			(wall) => {
				const { x, y } = cellToWorld(wall.col, wall.row);
				return new WallView(this.scene, x, y);
			},
			() => {},
			(view) => view.destroy(),
		);
	}

	breakWall(id: string, onComplete?: () => void): void {
		const wall = this.wallViews.get(id);
		if (!wall) return;
		wall.break(() => {
			this.wallViews.delete(id);
			onComplete?.();
		});
	}

	hasWallAt(col: number, row: number): string | null {
		const id = cellKey(col, row);
		return this.wallViews.has(id) ? id : null;
	}

	/* --- Items --- */ 

	addItem(item: ItemData): void {
		if (this.itemViews.has(item.id)) return;
		const { x, y } = cellToWorld(item.col, item.row);
		const view = new ItemView(
			this.scene,
			item.type,
			x,
			y,
		);
		this.itemViews.set(item.id, view);
	}

	syncItems(items: ItemData[]): void {
		reconcileViews(
			this.itemViews,
			items,
			(item) => {
				const { x, y } = cellToWorld(item.col, item.row);
				return new ItemView(this.scene, item.type, x, y);
			},
			() => {},
			(view) => view.destroy(),
		);
	}

	removeItem(id: string): void {
		this.itemViews.get(id)?.destroy();
		this.itemViews.delete(id);
	}

	/* --- Bombs --- */

	placeBomb(id: string, col: number, row: number, onComplete?: () => void): void {
		const { x, y } = cellToWorld(col, row);
		const bomb = new BombView(this.scene, x, y, () => {
			this.bombViews.delete(id);
			onComplete?.();
		});
		this.bombViews.set(id, bomb);
	}

	moveBomb(
		id: string,
		col: number,
		row: number,
	): void {
		const { x, y } = cellToWorld(col, row)

		this.bombViews
			.get(id)
			?.moveTo(x, y)
	}

	removeBomb(id: string): void {
		this.bombViews.get(id)?.destroy();
		this.bombViews.delete(id);
	}

	/* --- Explosions --- */

	triggerExplosion(
		centerCol: number,
		centerRow: number,
		hitCells: ExplosionHitCell[],
		destroyedWallIds: string[],
		onComplete?: () => void,
	): void {
		destroyedWallIds.forEach((id) => this.breakWall(id));

		new ExplosionView(this.scene, centerCol, centerRow, hitCells, () => {
			debugLog('[EXPLOSION] finished');
			onComplete?.();
		});
	}
}
