import { Injectable, OnModuleDestroy, OnModuleInit } from '@nestjs/common'
import { GameState } from './models/game-state'
import { PlayerColor } from './models/player'
import { BombDto, PowerUpDto } from './models/gameplay-dto'
import { GameStatus } from './types'
import { PlayerService } from './services/player.service'
import { MapService } from './services/map.service'
import { MovementService } from './services/movement.service'
import { BombService, ExplosionResult } from './services/bomb.service'
import { PowerUpService } from './services/power-up.service'
import { GameEngineEventsService } from './services/game-engine-events.service'
import { PowerUpType } from './models/power-up'
import { TileType } from './models/map'
import { DEBUG_SPAWN_POWERUPS } from './debug-config'
import { UserStatsService } from './services/user-stats.service'
import { XpService } from './services/xp.service'

import type {
	ActionResult,
	Direction,
	GameStateDTO,
	PlayerStateDTO,
} from './types'

export interface GamePlayerInput {
	id: number
	username: string
	color: PlayerColor
}

export interface BombPlacedResult {
	gameId: string
	bomb: BombDto
}

export interface PickedPowerUpResult {
	gameId: string
	playerId: number
	powerUp: PowerUpDto
}

const TICK_INTERVAL_MS = 50 // 20 Hz

@Injectable()
export class GameManagerService
	implements OnModuleInit, OnModuleDestroy
{

	private readonly games =
		new Map<string, GameState>()

	private readonly activeDirections =
		new Map<
			string,
			Map<number, Direction>
		>()

	private tickHandle:
		NodeJS.Timeout | null = null


	constructor(
		private readonly playerService:
			PlayerService,

		private readonly mapService:
			MapService,

		private readonly movementService:
			MovementService,

		private readonly bombService:
			BombService,

		private readonly powerUpService:
			PowerUpService,

		private readonly gameEngineEvents:
			GameEngineEventsService,
		
		private readonly userStatsService:
			UserStatsService,

		private readonly xpService:
			XpService,
	) {}


	/*----------------------------LIFECYCLE----------------------------*/

	onModuleInit(): void {
		this.tickHandle = setInterval(
			() => this.tickAll(),
			TICK_INTERVAL_MS,
		)
	}

	onModuleDestroy(): void {
		if (this.tickHandle) {
			clearInterval(
				this.tickHandle,
			)
		}
		this.tickHandle = null
	}

	/*----------------------------GAME CREATION----------------------------*/

	createGame(
		gameId: string,
		lobbyId: string,
		players: GamePlayerInput[],
	): GameState {

		if (this.games.has(gameId)) {
			throw new Error(
				`Game ${gameId} already exists`,
			)
		}
		const spawnPoints =
			this.mapService.getSpawnPoints(
				15,
				9,
				players.length,
			)
		const map =
			this.mapService.generateMap(spawnPoints)
		const state =
			new GameState(gameId, lobbyId, map)

		players.forEach(
			(playerInput, index) => {
				const spawn = spawnPoints[index]
				this.playerService
					.createPlayer(
						state,
						playerInput.id,
						playerInput.username,
						playerInput.color,
						spawn.x,
						spawn.y,
					)
			},
		)
		if (DEBUG_SPAWN_POWERUPS) {
			this.spawnDebugPowerUps(state)
		}
		this.games.set(gameId, state)
		this.activeDirections.set(gameId, new Map())
		return state
	}


	/*----------------------------GAME ACCESS----------------------------*/

	getGame(
		gameId: string,
	): GameState | undefined {
		return this.games.get(gameId)
	}

	hasGame(
		gameId: string,
	): boolean {
		return this.games.has(gameId)
	}

	getGameState(
		gameId: string,
	): GameStateDTO | undefined {
		const state = this.games.get(gameId)
		if (!state) {
			return undefined
		}
		return this.toDTO(state)
	}

	removeGame(
		gameId: string,
	): boolean {
		this.activeDirections.delete(gameId)
		this.movementService.clearGame(gameId)
		return this.games.delete(gameId)
	}


	/*----------------------------MOVEMENT----------------------------*/

	setPlayerDirection(
		gameId: string,
		playerId: number,
		direction: Direction,
	): ActionResult {
		const state = this.games.get(gameId)
		if (!state) {
			return {
				success: false,
				reason: 'game_not_found',
			}
		}
		if (state.status !== GameStatus.RUNNING) {
			return {
				success: false,
				reason: 'game_ended',
			}
		}
		const player = this.playerService.getPlayer(state, playerId)
		if (!player) {
			return {
				success: false,
				reason: 'player_not_found',
			}
		}
		if (!player.alive) {
			return {
				success: false,
				reason: 'player_dead',
			}
		}
		const directions = this.activeDirections.get(gameId)
		if (!directions) {
			return {
				success: false,
				reason: 'game_not_found',
			}
		}
		const previousDirection = directions.get(playerId)
		const isNewMovement = !previousDirection
		directions.set(playerId, direction)
		if (!isNewMovement) {
			return { success: true }
		}
		const previousBombPositions =
			this.getBombPositions(state)

		const moved = this.movementService.step(
			state,
			playerId,
			direction,
			this.mapService,
		)

		this.emitMovedBombs(
			state,
			gameId,
			previousBombPositions,
		)

		if (moved) {
			this.gameEngineEvents.emitPlayerMoved({
				gameId,
				players: [{
					id: player.id,
					x: player.x,
					y: player.y,
				}],
			})
			this.checkPowerUpPickup(state, gameId, playerId)
		}
		return { success: true }
	}


	stopPlayer(
		gameId: string,
		playerId: number,
	): ActionResult {
		const state = this.games.get(gameId)

		if (!state) {
			return {
				success: false,
				reason: 'game_not_found',
			}
		}

		this.activeDirections
			.get(gameId)
			?.delete(playerId)

		this.movementService.clearPlayer(gameId, playerId)
		return {success: true}
	}


	/*----------------------------BOMBS----------------------------*/

	placeBomb(
		gameId: string,
		playerId: number,
	): BombPlacedResult | undefined {

		const state = this.games.get(gameId)

		if (!state || state.status !== GameStatus.RUNNING)
			{return undefined}

		const player = this.playerService.getPlayer(state, playerId)

		if (!player || !player.alive) {
			return undefined
		}
		const bomb =
			this.bombService.createBomb(
				state,
				playerId,
				player.x,
				player.y,
			)

		if (!bomb) {
			return undefined
		}

		return {
			gameId,

			bomb: {
				id: bomb.id,
				playerId: bomb.playerId,
				x: bomb.x,
				y: bomb.y,
				range: bomb.range,
				damage: bomb.damage,
				placedAt: bomb.createdAt,
				explosionDelay:
					bomb.explosionDelay,
			},
		}
	}


	/*----------------------------DEBUG----------------------------*/

	private spawnDebugPowerUps(state: GameState): void {
		Object.values(PowerUpType).forEach((type, index) => {
			const x = index + 1
			const y = 0
			this.mapService.setTile(state.map, x, y, TileType.EMPTY)
			this.powerUpService.createPowerUp(state, type, x, y)
		})
		Object.values(PowerUpType).forEach((type, index) => {
			const x = index + 1
			const y = 2
			this.mapService.setTile(state.map, x, y, TileType.EMPTY)
			this.powerUpService.createPowerUp(state, type, x, y)
		})
	}


	/*----------------------------POWER-UP AUTO-PICKUP----------------------------*/

	private checkPowerUpPickup(state: GameState, gameId: string, playerId: number): void {
		const player = this.playerService.getPlayer(state, playerId)
		if (!player || !player.alive) {
			return
		}

		const powerUp = this.powerUpService.getPowerUpAt(state, player.x, player.y)
		if (!powerUp) {
			return
		}

		const collected = this.powerUpService.collectPowerUp(state, playerId, powerUp.id)
		if (!collected) {
			return
		}

		player.stats.powerUpsCollected++

		this.gameEngineEvents.emitPowerUpPicked({
			gameId,
			playerId,
			powerUp: {
				id: collected.id,
				type: collected.type,
				x: collected.x,
				y: collected.y,
			},
		})
	}


	/*----------------------------POWER UPS----------------------------*/

	pickPowerUp(
		gameId: string,
		playerId: number,
		powerUpId: string,
	): PickedPowerUpResult | undefined {

		const state = this.games.get(gameId)

		if (!state || state.status !== GameStatus.RUNNING) {
			return undefined
		}

		const powerUp =
			this.powerUpService
				.collectPowerUp(
					state,
					playerId,
					powerUpId,
				)

		if (!powerUp) {
			return undefined
		}

		return {
			gameId,
			playerId,

			powerUp: {
				id: powerUp.id,
				type: powerUp.type,
				x: powerUp.x,
				y: powerUp.y,
			},
		}
	}


	/*----------------------------DISCONNECT----------------------------*/

	disconnectPlayer(
		gameId: string,
		playerId: number,
	): void {

		const state = this.games.get(gameId)

		if (!state) {
			return
		}
		const player = this.playerService.getPlayer(state, playerId)

		if (player) {
			player.alive = false
			this.gameEngineEvents.emitPlayerDead({ gameId, playerId })
		}

		this.stopPlayer(gameId, playerId)
		this.checkVictory(gameId)
	}


	/*----------------------------GAME LOOP----------------------------*/

	private tickAll(): void {

		const dt = TICK_INTERVAL_MS / 1000

		this.games.forEach(
			(state, gameId) => {
				if (state.status !== GameStatus.RUNNING) {
					return
				}
				this.tickMovement(state, gameId, dt)
				const explosions = this.tickBombs(state)
				const emittedDeaths = new Set<number>()
				for (const result of explosions) {
					this.gameEngineEvents.emitBombExploded({gameId, result})

					for (const playerId of result.deadPlayers) {
						if (emittedDeaths.has(playerId)) continue
							emittedDeaths.add(playerId)
						this.gameEngineEvents.emitPlayerDead({ gameId, playerId })
					}
				}
				this.checkVictory(gameId)
			},
		)
	}

	private getBombPositions(
		state: GameState,
	): Map<string, { x: number; y: number }> {
		const positions = new Map<
			string,
			{ x: number; y: number }
		>()

		for (const bomb of this.bombService.getBombs(state)) {
			positions.set(bomb.id, {
				x: bomb.x,
				y: bomb.y,
			})
		}

		return positions
	}

	private emitMovedBombs(
		state: GameState,
		gameId: string,
		previousPositions: Map<string, { x: number; y: number }>,
	): void {
		for (const bomb of this.bombService.getBombs(state)) {
			const previous = previousPositions.get(bomb.id)

			if (!previous)
				continue

			if (
				previous.x === bomb.x &&
				previous.y === bomb.y
			) {
				continue
			}

			this.gameEngineEvents.emitBombMoved({
				gameId,
				bomb: {
					id: bomb.id,
					x: bomb.x,
					y: bomb.y,
				},
			})
		}
	}

	private tickMovement(
		state: GameState,
		gameId: string,
		dt: number,
	): void {
		const directions = this.activeDirections.get(gameId)
		if (!directions || directions.size === 0) return

		const previousBombPositions =
			this.getBombPositions(state)

		const moved = this.movementService.advance(
			state,
			directions,
			dt,
			this.mapService,
		)

		this.emitMovedBombs(
			state,
			gameId,
			previousBombPositions,
		)

		if (!moved) return
		const players: {
			id: number
			x: number
			y: number
		}[] = []
		for (const playerId of directions.keys()) {
			const player = state.players.get(playerId)
			if (!player || !player.alive) continue
			players.push({
				id: player.id,
				x: player.x,
				y: player.y,
			})
		}
		if (players.length === 0) {
			return
		}
		this.gameEngineEvents
			.emitPlayerMoved({
				gameId,
				players,
			})
		players.forEach((p) => this.checkPowerUpPickup(state, gameId, p.id))
	}


	private tickBombs(
		state: GameState,
	): ExplosionResult[] {
		const results: ExplosionResult[] = []


		const bombs =
			this.bombService
				.getBombsToExplode(state)

		for (const bomb of bombs) {

			if (
				bomb.hasExploded() ||
				!this.bombService.hasBomb(
					state,
					bomb.id,
				)
			) {
				continue
			}
			const result =
				this.bombService
					.explodeBomb(
						state,
						bomb.id,
					)
			if (result) {
				results.push(result)
			}
		}
		return results
	}


	/*----------------------------VICTORY----------------------------*/

	private checkVictory(
		gameId: string,
	): void {
		const state = this.games.get(gameId)

		if (!state || state.status !== GameStatus.RUNNING) {
			return
		}

		if (state.players.size < 2) {
			return
		}

		const alive = this.playerService.getAlivePlayers(state)

		if (alive.length > 1) {
			return
		}

		const winnerId =
			alive.length === 1
				? alive[0].id
				: null

		this.endGame(state, winnerId)
	}

	private async endGame(
		state: GameState,
		winnerId: number | null,
	): Promise<void> {

		state.status = GameStatus.ENDED
		state.winnerId = winnerId
		state.endedAt = Date.now()

		if (winnerId !== null) {
			const winner = this.playerService.getPlayer(
				state,
				winnerId,
			)

			if (winner) {
				winner.stats.gamesWon++
			}
		}

		const players = this.playerService
            .getPlayers(state)
            .map((player) => {
                const xp = this.xpService.calculate(player)
            
                console.log(
                    `player ${player.id} -> +${xp} XP`,
                    player.stats,
                )
            
                return {
                    id: player.id,
                    xp,
                    stats: {
                        bombsPlaced: player.stats.bombsPlaced,
                        blocksDestroyed: player.stats.blocksDestroyed,
                        kills: player.stats.kills,
                        powerUpsCollected: player.stats.powerUpsCollected,
                    },
                }
            })

		await Promise.all(
			players.map((player) =>
				this.userStatsService.recordGameResult(
					player.id,
					winnerId === null
						? 'draw'
						: player.id === winnerId
							? 'win'
							: 'loss',
					player.stats.bombsPlaced,
					player.stats.kills,
					player.xp,
				),
			),
		)

		this.activeDirections
			.get(state.gameId)
			?.clear()

		this.movementService.clearGame(state.gameId)
		this.gameEngineEvents.emitGameEnded({gameId: state.gameId,
			lobbyId: state.lobbyId,
			winnerId,
			players,
		})
	}

	/*----------------------------DTO----------------------------*/

	private toDTO(
		state: GameState,
	): GameStateDTO {

		const players:
			PlayerStateDTO[] =
			this.playerService
				.getPlayers(state)
				.map((player) => ({
					id: player.id,
					username:
						player.username,
					color:
						player.color,
					x: player.x,
					y: player.y,
					alive:
						player.alive,
					speed:
						player.speed,
					maxBombs:
						player.maxBombs,
					availableBombs:
						player.availableBombs,
					flameRange:
						player.flameRange,
					canKickBombs:
						player.canKickBombs,
				}))


		const bombs: BombDto[] =
			this.bombService
				.getBombs(state)
				.map((bomb) => ({
					id: bomb.id,
					playerId:
						bomb.playerId,
					x: bomb.x,
					y: bomb.y,
					range:
						bomb.range,
					damage:
						bomb.damage,
					placedAt:
						bomb.createdAt,
					explosionDelay:
						bomb.explosionDelay,
				}))


		const powerUps: PowerUpDto[] =
			this.powerUpService
				.getPowerUps(state)
				.filter(
					(powerUp) =>
						!powerUp.isCollected(),
				)
				.map((powerUp) => ({
					id: powerUp.id,
					type:
						powerUp.type,
					x: powerUp.x,
					y: powerUp.y,
				}))


		return {
			gameId: state.gameId,
			status: state.status,
			map: {
				cols: state.map.width,
				rows: state.map.height,
				tiles: this.mapService
						.toGrid(state.map),
			},
			players,
			bombs,
			powerUps,
			winnerId: state.winnerId,
		}
	}
}
