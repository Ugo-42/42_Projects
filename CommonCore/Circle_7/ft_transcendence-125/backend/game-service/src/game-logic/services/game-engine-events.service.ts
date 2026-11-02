import { Injectable } from '@nestjs/common'
import { EventEmitter } from 'events'
import { PowerUpType } from '../models/power-up'

export interface PlayerMovedEvent {
	gameId: string
	players: {
		id: number
		x: number
		y: number
	}[]
}

export interface BombMovedEvent {
	gameId: string
	bomb: {
		id: string
		x: number
		y: number
	}
}

export interface PlayerDeadEvent {
	gameId: string
	playerId: number
}

export interface BombExplodedEvent {
	gameId: string
	result: {
		bombId: string
		playerId: number

		explosions: {
			bombId: string
			playerId: number
			center: {
				x: number
				y: number
			}
			cells: {
				x: number
				y: number
			}[]
		}[]

		destroyedBlocks: {
			x: number
			y: number
		}[]

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
}

export interface PowerUpPickedEvent {
	gameId: string
	playerId: number
	powerUp: {
		id: string
		type: PowerUpType
		x: number
		y: number
	}
}

export interface GameEndedPlayer {
	id: number
	xp: number
}

export interface GameEndedEvent {
	gameId: string
	lobbyId: string
	winnerId: number | null
	players: GameEndedPlayer[]
}


type PlayerMovedListener = (payload: PlayerMovedEvent) => void
type BombMovedListener = (payload: BombMovedEvent) => void
type PlayerDeadListener = (payload: PlayerDeadEvent) => void
type PowerUpPickedListener = (payload: PowerUpPickedEvent) => void
type BombExplodedListener = (payload: BombExplodedEvent) => void
type GameEndedListener = (payload: GameEndedEvent) => void

@Injectable()
export class GameEngineEventsService {
	private readonly emitter = new EventEmitter()
	private static readonly PLAYER_MOVED = 'player-moved'
	private static readonly BOMB_MOVED = 'bomb-moved'
	private static readonly PLAYER_DEAD = 'player-dead'
	private static readonly BOMB_EXPLODED = 'bomb-exploded'
	private static readonly POWERUP_PICKED = 'powerup-picked'
	private static readonly GAME_ENDED = 'game-ended'

	emitPlayerMoved(payload: PlayerMovedEvent): void {
		this.emitter.emit(GameEngineEventsService.PLAYER_MOVED, payload)
	}

	onPlayerMoved(listener: PlayerMovedListener): () => void {
		this.emitter.on(GameEngineEventsService.PLAYER_MOVED, listener)
		return () => {
			this.emitter.off(GameEngineEventsService.PLAYER_MOVED, listener)
		}
	}

	emitBombExploded(payload: BombExplodedEvent): void {
		this.emitter.emit(
			GameEngineEventsService.BOMB_EXPLODED,
			payload,
		)
	}

	onBombExploded(
		listener: BombExplodedListener,
	): () => void {
		this.emitter.on(
			GameEngineEventsService.BOMB_EXPLODED,
			listener,
		)
		return () => {
			this.emitter.off(
				GameEngineEventsService.BOMB_EXPLODED,
				listener,
			)
		}
	}

	emitBombMoved(payload: BombMovedEvent): void {
		this.emitter.emit(
			GameEngineEventsService.BOMB_MOVED,
			payload,
		)
	}

	onBombMoved(
		listener: BombMovedListener,
	): () => void {
		this.emitter.on(
			GameEngineEventsService.BOMB_MOVED,
			listener,
		)

		return () => {
			this.emitter.off(
				GameEngineEventsService.BOMB_MOVED,
				listener,
			)
		}
	}
	
	emitPowerUpPicked(payload: PowerUpPickedEvent): void {
		this.emitter.emit(GameEngineEventsService.POWERUP_PICKED, payload)
	}

	onPowerUpPicked(listener: PowerUpPickedListener): () => void {
		this.emitter.on(GameEngineEventsService.POWERUP_PICKED, listener)
		return () => {
			this.emitter.off(GameEngineEventsService.POWERUP_PICKED, listener)
		}
	}

	emitPlayerDead(payload: PlayerDeadEvent): void {
		this.emitter.emit(GameEngineEventsService.PLAYER_DEAD, payload)
	}

	onPlayerDead(listener: PlayerDeadListener): () => void {
		this.emitter.on(GameEngineEventsService.PLAYER_DEAD, listener)
		return () => {
			this.emitter.off(GameEngineEventsService.PLAYER_DEAD, listener)
		}
	}

	emitGameEnded(payload: GameEndedEvent): void {
		this.emitter.emit(
			GameEngineEventsService.GAME_ENDED,
			payload,
		)
	}

	onGameEnded(
		listener: GameEndedListener,
	): () => void {
		this.emitter.on(
			GameEngineEventsService.GAME_ENDED,
			listener,
		)
		return () => {
			this.emitter.off(
				GameEngineEventsService.GAME_ENDED,
				listener,
			)
		}
	}

}
