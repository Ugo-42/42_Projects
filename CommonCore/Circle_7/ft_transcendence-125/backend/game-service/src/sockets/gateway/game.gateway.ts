import { UseGuards } from '@nestjs/common'

import {
	ConnectedSocket,
	MessageBody,
	SubscribeMessage,
	WebSocketGateway,
	WebSocketServer,
} from '@nestjs/websockets'

import { OnModuleDestroy } from '@nestjs/common'
import { OnGatewayInit } from '@nestjs/websockets'
import { GameEngineEventsService } from '../../game-logic/services/game-engine-events.service'
import { Server } from 'socket.io'
import { GAME_EVENTS } from '../constants/game.events'
import { LOBBY_EVENTS } from '../constants/lobby.events'
import { getGameRoom, getLobbyRoom } from '../constants/room-names'
import { GameRoomDto } from '../dto/game-room.dto'
import { LobbyRoomDto } from '../dto/lobby-room.dto'
import { GameManagerService } from '../../game-logic/game-manager.service'
import { PlayerMoveDto } from '../dto/player-move.dto'
import { AuthenticatedGameSocket } from '../interfaces/game-socket.interface'
import { JwtWsGuard } from './jwt-ws.guard'


@WebSocketGateway({
	namespace: '/game',
	cors: true,
})
export class GameGateway 
	implements
		OnGatewayInit,
		OnModuleDestroy
	{
	constructor(
		private readonly gameManagerService:
			GameManagerService,
		private readonly gameEngineEvents:
			GameEngineEventsService,
	) {}

	private unsubscribePlayerMoved: (() => void) | null = null
	private unsubscribePlayerDead: (() => void) | null = null
	private unsubscribeBombExploded: (() => void) | null = null
	private unsubscribeBombMoved: (() => void) | null = null
	private unsubscribePowerUpPicked: (() => void) | null = null
	private unsubscribeGameEnded: (() => void) | null = null

	@WebSocketServer()
	server!: Server

	afterInit(
		server: Server,
	): void {
		this.unsubscribePlayerMoved =
			this.gameEngineEvents
				.onPlayerMoved(
					(payload) => {
						server.to(getGameRoom(payload.gameId))
							.emit(
								GAME_EVENTS.PLAYER_MOVED,
								payload,
							)
					},
				)

		this.unsubscribePlayerDead =
			this.gameEngineEvents
				.onPlayerDead(
					(payload) => {
						server.to(getGameRoom(payload.gameId))
						.emit(GAME_EVENTS.PLAYER_DEAD,
							  payload,
							 )
					},
				)
		
		this.unsubscribeBombMoved =
			this.gameEngineEvents
				.onBombMoved(
					(payload) => {
						server
							.to(getGameRoom(payload.gameId))
							.emit(
								GAME_EVENTS.BOMB_MOVED,
								payload,
							)
					},
				)

		this.unsubscribeBombExploded =
			this.gameEngineEvents
				.onBombExploded(
					(payload) => {
						server.to(getGameRoom(payload.gameId))
							.emit(
								GAME_EVENTS.BOMB_EXPLODED,
								payload,
							)
					},
				)

		this.unsubscribePowerUpPicked =
			this.gameEngineEvents
				.onPowerUpPicked(
					(payload) => {
						server.to(getGameRoom(payload.gameId))
						.emit(GAME_EVENTS.POWERUP_PICKED,
							  payload,
							 )
					},
				)
		
		this.unsubscribeGameEnded =
			this.gameEngineEvents
				.onGameEnded(
					(payload) => {
						server.to(getGameRoom(payload.gameId))
							.emit(
								GAME_EVENTS.GAME_ENDED,
								payload,
							)
					},
				)
	}

	onModuleDestroy(): void {
		this.unsubscribePlayerMoved?.()
		this.unsubscribePlayerMoved = null
		this.unsubscribePlayerDead?.()
		this.unsubscribePlayerDead = null
		this.unsubscribeBombExploded?.()
		this.unsubscribeBombExploded = null
		this.unsubscribeBombMoved?.()
		this.unsubscribeBombMoved = null
		this.unsubscribePowerUpPicked?.()
		this.unsubscribePowerUpPicked = null
		this.unsubscribeGameEnded?.()
		this.unsubscribeGameEnded = null
	}
	/*----------------------------LOBBY JOIN----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(LOBBY_EVENTS.JOIN)
	async handleLobbyJoin(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: LobbyRoomDto,
	) {
		const { lobbyId } = payload
		const userId =
			Number(client.data.user.sub)

		const room =
			getLobbyRoom(lobbyId)

		await client.join(room)

		console.log(
			`[LOBBY SOCKET] User ${userId} joined ${room}`,
		)

		return {
			success: true,
			lobbyId,
		}
	}


	/*----------------------------LOBBY LEAVE----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(LOBBY_EVENTS.LEAVE)
	async handleLobbyLeave(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: LobbyRoomDto,
	) {
		const { lobbyId } = payload
		const userId =
			Number(client.data.user.sub)

		const room =
			getLobbyRoom(lobbyId)

		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_LOBBY_ROOM',
			}
		}

		await client.leave(room)

		console.log(
			`[LOBBY SOCKET] User ${userId} left ${room}`,
		)

		return {
			success: true,
			lobbyId,
		}
	}


	/*----------------------------GAME JOIN----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(GAME_EVENTS.JOIN)
	async handleGameJoin(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: GameRoomDto,
	) {
		const { gameId } = payload
		const userId = Number(client.data.user.sub)
		const game = this.gameManagerService.getGame(gameId)
		if (!game) {
			return {
				success: false,
				error: 'NOT_NOT_FOUND',
			}
		}
		if (!game.players.has(userId)) {
			return {
				success: false,
				error: 'NOT_GAME_PLAYER',
			}
		}

		const room = getGameRoom(gameId)

		await client.join(room)

		console.log(
			`[GAME SOCKET] User ${userId} joined ${room}`,
		)
		const state = this.gameManagerService.getGameState(gameId)
		if (state) {
			console.log("[GAME SOCKET] Sending game:state", gameId, state)
			client.emit(
				GAME_EVENTS.STATE,
				state
			)
		}

		return {
			success: true,
			gameId,
		}
	}


	/*----------------------------GAME LEAVE----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(GAME_EVENTS.LEAVE)
	async handleGameLeave(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: GameRoomDto,
	) {
		const { gameId } = payload
		const userId =
			Number(client.data.user.sub)

		const room =
			getGameRoom(gameId)

		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_GAME_ROOM',
			}
		}

		await client.leave(room)

		console.log(
			`[GAME SOCKET] User ${userId} left ${room}`,
		)

		return {
			success: true,
			gameId,
		}
	}

	/*----------------------------PLAYER MOOVE----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(GAME_EVENTS.PLAYER_MOVE)
	handlePlayerMove(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: PlayerMoveDto,
	) {
		const {
			gameId,
			dirX,
			dirY,
		} = payload
		const userId = Number(client.data.user.sub)
		const room = getGameRoom(gameId)

		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_GAME_ROOM',
			}
		}

		const result = this.gameManagerService
				.setPlayerDirection(
					gameId,
					userId,
					{
						dirX,
						dirY,
					},
				)

		if (!result.success) {
			return {
				success: false,
				error:
					result.reason ??
					'MOVE_REJECTED',
			}
		}
		return {success: true}
	}

	/*----------------------------PLAYER STOP----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(GAME_EVENTS.PLAYER_STOP)
	handlePlayerStop(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: GameRoomDto,
	) {

		const { gameId } = payload

		const userId =
			Number(client.data.user.sub)


		const room =
			getGameRoom(gameId)


		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_GAME_ROOM',
			}
		}


		const result =
			this.gameManagerService
				.stopPlayer(
					gameId,
					userId,
				)


		if (!result.success) {
			return {
				success: false,
				error:
					result.reason ??
					'STOP_REJECTED',
			}
		}


		return {
			success: true,
		}
	}

	/*----------------------------BOMB PLACE----------------------------*/

	@UseGuards(JwtWsGuard)
	@SubscribeMessage(GAME_EVENTS.BOMB_PLACE)
	handleBombPlace(
		@ConnectedSocket()
		client: AuthenticatedGameSocket,

		@MessageBody()
		payload: GameRoomDto,
	) {
		const { gameId } = payload
		const userId = Number(client.data.user.sub)
		const room = getGameRoom(gameId)
		if (!client.rooms.has(room)) {
			return {
				success: false,
				error: 'NOT_IN_GAME_ROOM',
			}
		}
		const result =
			this.gameManagerService
				.placeBomb(gameId, userId)
		if (!result) {
			return {
				success: false,
				error: 'BOMB_PLACE_REJECTED',
			}
		}

		this.server
			.to(room)
			.emit(
				GAME_EVENTS.BOMB_PLACED,
				result,
			)
		return {success: true}
	}

}
