import {
	joinGame,
	movePlayer,
	stopPlayer,
	placeBomb,
	onGameState,
	onBombExploded,
	onBombMoved,
	onBombPlaced,
	onPlayerMoved,
	onPlayerDead,
	onPowerUpPicked,
	onGameEnded,
	type GameEndedPayload
} from "@/services/gameSocketService"

import { cellKey } from "../config/gridConfig"
import type { GameApi, ItemData } from "../api/GameApi"
import { characterTextureKey, type CharacterColor } from "../config/characterConfig"
import { powerUpTypeToItemType } from "../config/itemConfig"
import { debugLog } from "../config/debugConfig"

export interface RemotePlayerPosition {
	id: number
	x: number
	y: number
}

type PlayerMovedPayload = {
	gameId: string
	players: RemotePlayerPosition[]
}

interface GameStateMap {
	cols: number
	rows: number
	tiles: string[][]
}

interface PlayerDeadPayload {
	gameId: string
	playerId: number
}

interface GameStatePlayer {
	id: number
	username: string
	color: string
	x: number
	y: number
	alive: boolean
	speed: number
	maxBombs: number
	availableBombs: number
	flameRange: number
	canKickBombs: boolean
}

interface GameStatePowerUp {
	id: string
	type: string
	x: number
	y: number
}

interface GameStatePayload {
	gameId: string
	status: string
	map: GameStateMap
	players: GameStatePlayer[]
	bombs: unknown[]
	powerUps: GameStatePowerUp[]
	winnerId: number | null
}

interface ExplosionCell {
	x: number
	y: number
}

interface ExplosionData {
	bombId: string
	playerId: number
	center: ExplosionCell
	cells: ExplosionCell[]
}

interface BombExplodedResult {
	bombId: string
	playerId: number
	explosions: ExplosionData[]

	destroyedBlocks: ExplosionCell[]

	powerUps: {
		id: string
		type: string
		x: number
		y: number
	}[]

	spawnedPowerUps: {
		id: string
		type: string
		x: number
		y: number
	}[]

	hitPlayers: number[]
	deadPlayers: number[]
	chainReactionBombIds: string[]
}

interface BombExplodedPayload {
	gameId: string
	result: BombExplodedResult
}

interface BombPosition {
	col: number
	row: number
}

interface PowerUpPickedPayload {
	gameId: string
	playerId: number
	powerUp: GameStatePowerUp
}

export class RemoteGameClient {
	private readonly gameId: string
	private readonly api: GameApi
	private readonly cleanupListeners: Array<() => void> = []
	private lastSentDirection = { dirX: 0, dirY: 0 }
	private readonly bombs = new Map<string, BombPosition>()
	private readonly playerNames = new Map<number, string>()
	private readonly onGameEndedCallback?: (
		winnerId: number | null,
		winnerName: string | null,
		data: GameEndedPayload
	) => void

	constructor(
		gameId: string,
		api: GameApi,
		onGameEndedCallback?: (
			winnerId: number | null,
			winnerName: string | null,
			data: GameEndedPayload
		) => void
	) {
		this.gameId = gameId
		this.api = api
		this.onGameEndedCallback = onGameEndedCallback

		this.cleanupListeners.push(
			onGameState((data) => this.handleState(data as GameStatePayload)),
			onBombPlaced((data) => this.handleBombPlaced(data)),
			onBombMoved((data) => this.handleBombMoved(data)),
			onBombExploded((data) => this.handleBombExploded(data)),
			onPlayerMoved((payload) => this.handlePlayerMoved(payload)),
			onPlayerDead((payload) => this.handlePlayerDead(payload as PlayerDeadPayload)),
			onPowerUpPicked((payload) => this.handlePowerUpPicked(payload as PowerUpPickedPayload)),
			onGameEnded((data) => this.handleGameEnded(data)),
		)

		void this.join()
	}

	private async join(): Promise<void> {
		try {
			const result = await joinGame(this.gameId)

			if (!result.success) {
				console.error("[GAME] Failed to join game:", result.error)
				return
			}

			debugLog(`[GAME] Joined game room ${this.gameId}`)
		} catch (error) {
			console.error("[GAME] Failed to join game:", error)
		}
	}

	private handleState(payload: GameStatePayload): void {
		if (payload.gameId !== this.gameId) return
		debugLog("[GAME] state snapshot", payload)
		payload.players.forEach((player) => {
			this.playerNames.set(player.id, player.username)

			const id = String(player.id)
			if (!this.api.hasPlayer(id)) {
				const characterKey = characterTextureKey(
					player.color as CharacterColor
				)
				this.api.spawnPlayerAtWorld(
					id,
					characterKey,
					player.x,
					player.y
				)
				return
			}
			this.api.movePlayer(id, player.x, player.y)
		})
		this.syncWalls(payload.map)
		this.syncPowerUps(payload.powerUps)
	}

	private syncPowerUps(powerUps: GameStatePowerUp[]): void {
		const items: ItemData[] = []

		powerUps.forEach((powerUp) => {
			const type = powerUpTypeToItemType(powerUp.type)

			if (!type) {
				console.warn("[GAME] Unknown power-up type:", powerUp.type)
				return
			}

			items.push({ id: powerUp.id, type, col: powerUp.x, row: powerUp.y })
		})

		this.api.syncItems(items)
	}

	private syncWalls(map: GameStateMap): void {
		const walls = []
		for (let row = 0; row < map.rows; row++) {
			for (let col = 0; col < map.cols; col++) {
				if (map.tiles[row]?.[col] !== 'fragile_block') {
					continue
				}
				walls.push({
					id: cellKey(col, row),
					col,
					row,
				})
			}
		}
		this.api.syncWalls(walls)
	}

	private handlePlayerMoved(payload: PlayerMovedPayload): void {
		if (payload.gameId !== this.gameId) return

		payload.players.forEach((player) => {
			const id = String(player.id)
			this.api.movePlayer(id, player.x, player.y)
		})
	}

	private handlePlayerDead(payload: PlayerDeadPayload): void {
		if (payload.gameId !== this.gameId) return

			this.api.killPlayer(String(payload.playerId))
	}

	private handleBombPlaced(data: unknown): void {
		const payload = data as {
			gameId: string
			bomb: {
				id: string
				playerId: number
				x: number
				y: number
				range: number
				damage: number
				placedAt: number
				explosionDelay: number
			}
		}

		if (payload.gameId !== this.gameId) return

		const bomb = payload.bomb

		this.bombs.set(bomb.id, {
			col: bomb.x,
			row: bomb.y,
		})

		this.api.placeBomb(
			bomb.id,
			bomb.x,
			bomb.y,
		)
	}

	private handleBombMoved(data: unknown): void {
		const payload = data as {
			gameId: string
			bomb: {
				id: string
				x: number
				y: number
			}
		}
		if (payload.gameId !== this.gameId)
			return
		const bomb = payload.bomb
		const position = {
			col: bomb.x,
			row: bomb.y,
		}
		this.bombs.set(
			bomb.id,
			position,
		)
		this.api.moveBomb(
			bomb.id,
			bomb.x,
			bomb.y,
		)
	}

	private handleBombExploded(data: unknown): void {
		const payload = data as BombExplodedPayload

		if (payload.gameId !== this.gameId) return

		const result = payload.result

		this.bombs.delete(result.bombId)
		this.api.removeBomb(result.bombId)

		result.chainReactionBombIds.forEach((bombId) => {
			this.bombs.delete(bombId)
			this.api.removeBomb(bombId)
		})

		result.explosions.forEach((explosion) => {
			const hitCells = this.buildExplosionHitCells(
				explosion.center.x,
				explosion.center.y,
				explosion.cells,
			)

			const destroyedWallIds = result.destroyedBlocks
				.filter((cell) =>
					explosion.cells.some(
						(explosionCell) =>
							explosionCell.x === cell.x &&
							explosionCell.y === cell.y,
					),
				)
				.map((cell) => cellKey(cell.x, cell.y))

			this.api.triggerExplosion(
				explosion.center.x,
				explosion.center.y,
				hitCells,
				destroyedWallIds,
			)
		})

		result.spawnedPowerUps.forEach((powerUp) => {
			const type = powerUpTypeToItemType(powerUp.type)

			if (!type) {
				console.warn(
					"[GAME] Unknown spawned power-up type:",
					powerUp.type,
				)
				return
			}

			this.api.addItem({
				id: powerUp.id,
				type,
				col: powerUp.x,
				row: powerUp.y,
			})
		})
	}
	
	private buildExplosionHitCells(
		centerCol: number,
		centerRow: number,
		cells: ExplosionCell[],
	): {
		col: number
		row: number
		kind: 'side' | 'tip'
	}[] {
		return cells.map((cell) => {
			const dx = Math.sign(cell.x - centerCol)
			const dy = Math.sign(cell.y - centerRow)

			const distance =
				Math.abs(cell.x - centerCol) +
				Math.abs(cell.y - centerRow)

			const hasFurtherCell = cells.some((other) => {
				const otherDx = Math.sign(other.x - centerCol)
				const otherDy = Math.sign(other.y - centerRow)

				if (otherDx !== dx || otherDy !== dy) {
					return false
				}

				const otherDistance =
					Math.abs(other.x - centerCol) +
					Math.abs(other.y - centerRow)

				return otherDistance > distance
			})

			return {
				col: cell.x,
				row: cell.y,
				kind: hasFurtherCell ? 'side' : 'tip',
			}
		})
	}

	private handlePowerUpPicked(payload: PowerUpPickedPayload): void {
		if (payload.gameId !== this.gameId) return

		this.api.removeItem(payload.powerUp.id)
	}

	private handleGameEnded(data: GameEndedPayload): void {
		if (data.gameId !== this.gameId) return

		debugLog("[GAME] Game ended", data)

		const winnerName =
			data.winnerId === null
				? null
				: this.playerNames.get(data.winnerId) ?? null

		this.onGameEndedCallback?.(
			data.winnerId,
			winnerName,
			data,
		)
	}

	sendMove(dirX: number, dirY: number): void {
		if (
			this.lastSentDirection.dirX === dirX &&
			this.lastSentDirection.dirY === dirY
		) return

		this.lastSentDirection = { dirX, dirY }
		movePlayer(this.gameId, dirX, dirY)
	}

	sendStop(): void {
		this.lastSentDirection = { dirX: 0, dirY: 0 }
		stopPlayer(this.gameId)
	}

	sendBombPlace(): void {
		placeBomb(this.gameId)
	}

	destroy(): void {
		this.cleanupListeners.forEach((cleanup) => cleanup())
		this.cleanupListeners.length = 0
	}
}
