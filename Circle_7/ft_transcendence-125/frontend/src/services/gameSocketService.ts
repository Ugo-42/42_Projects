import type { Socket } from "socket.io-client"

import {
	connectSocket,
	getGameSocket,
} from "@/services/socketService"

import { GAME_EVENTS } from "@/services/game.events"


type GameRoomPayload = {gameId: string}

type MovePayload = {
	gameId: string
	dirX: number
	dirY: number
}

export interface PlayerMovedPayload {
	gameId: string
	players: {
		id: number
		x: number
		y: number
	}[]
}

type GamePayload = {gameId: string}


export type GameRoomAck =
	| { success: true
		gameId: string }
	| { success: false
		error: string 
	}

export interface GameEndedPlayer {
	id: number
	xp: number

	stats: {
		bombsPlaced: number
		blocksDestroyed: number
		kills: number
		deaths: number
		powerUpsCollected: number
	}
}

export interface GameEndedPayload {
	gameId: string
	lobbyId: string
	winnerId: number | null
	players: GameEndedPlayer[]
}

function getSocket(): Socket {

	const socket = getGameSocket() ?? connectSocket()
	if (!socket) {
		throw new Error("GAME_SOCKET_UNAVAILABLE")
	}
	return socket
}


function waitForConnection(
	socket: Socket,
): Promise<void> {

	if (socket.connected) {
		return Promise.resolve()
	}

	return new Promise(
		(resolve, reject) => {

			const handleConnect = () => {
				cleanup()
				resolve()
			}

			const handleError = (
				error: Error,
			) => {
				cleanup()
				reject(error)
			}

			const cleanup = () => {
				socket.off(
					"connect",
					handleConnect,
				)

				socket.off(
					"connect_error",
					handleError,
				)
			}

			socket.once(
				"connect",
				handleConnect,
			)

			socket.once(
				"connect_error",
				handleError,
			)
		},
	)
}


async function emitRoomEvent(
	event: typeof GAME_EVENTS.JOIN
		| typeof GAME_EVENTS.LEAVE,
	gameId: string,
): Promise<GameRoomAck> {

	const socket = getSocket()

	await waitForConnection(socket)

	const payload: GameRoomPayload = {
		gameId,
	}

	return socket
		.timeout(5000)
		.emitWithAck(
			event,
			payload,
		)
}


/*----------------------------ROOM----------------------------*/

export function joinGame(
	gameId: string,
): Promise<GameRoomAck> {

	return emitRoomEvent(
		GAME_EVENTS.JOIN,
		gameId,
	)
}


export function leaveGame(
	gameId: string,
): Promise<GameRoomAck> {

	return emitRoomEvent(
		GAME_EVENTS.LEAVE,
		gameId,
	)
}


/*----------------------------INPUT----------------------------*/

export function movePlayer(
	gameId: string,
	dirX: number,
	dirY: number,
): void {

	const socket = getSocket()

	const payload: MovePayload = {
		gameId,
		dirX,
		dirY,
	}

	socket.emit(
		GAME_EVENTS.PLAYER_MOVE,
		payload,
	)
}


export function stopPlayer(
	gameId: string,
): void {

	const socket = getSocket()

	const payload: GamePayload = {
		gameId,
	}

	socket.emit(
		GAME_EVENTS.PLAYER_STOP,
		payload,
	)
}


export function placeBomb(
	gameId: string,
): void {

	const socket = getSocket()

	const payload: GamePayload = {
		gameId,
	}

	socket.emit(
		GAME_EVENTS.BOMB_PLACE,
		payload,
	)
}


/*----------------------------STATE----------------------------*/

export function onGameState(callback: (data: unknown) => void): () => void {
	const socket = getSocket()
	const handler = (data: unknown) => {
		console.log("[SOCKET] RECEIVED game:state", data)
		callback(data)
	}

	socket.on(GAME_EVENTS.STATE, handler)

	return () => {
		socket.off(GAME_EVENTS.STATE, handler)
	}
}

let lastMovedAt = performance.now()

export function onPlayerMoved(
	callback: (data: PlayerMovedPayload) => void,
): () => void {

	const socket = getSocket()

	const handler = (
		data: PlayerMovedPayload,
	) => {

		const now =
			performance.now()

		console.log(
			"[PLAYER_MOVED]",
			Math.round(
				now - lastMovedAt,
			),
			"ms",
			data,
		)

		lastMovedAt = now

		callback(data)
	}


	socket.on(
		GAME_EVENTS.PLAYER_MOVED,
		handler
	)

	return () => {
		socket.off(
			GAME_EVENTS.PLAYER_MOVED,
			handler
		)
	}
}


export function onPlayerDead(
	callback: (data: unknown) => void,
): () => void {

	const socket = getSocket()

	socket.on(
		GAME_EVENTS.PLAYER_DEAD,
		callback,
	)

	return () => {
		socket.off(
			GAME_EVENTS.PLAYER_DEAD,
			callback,
		)
	}
}


/*----------------------------BOMBS----------------------------*/

export function onBombPlaced(
	callback: (data: unknown) => void,
): () => void {

	const socket = getSocket()

	socket.on(
		GAME_EVENTS.BOMB_PLACED,
		callback,
	)

	return () => {
		socket.off(
			GAME_EVENTS.BOMB_PLACED,
			callback,
		)
	}
}

export function onBombMoved(
	callback: (data: unknown) => void,
): () => void {

	const socket = getSocket()

	socket.on(
		GAME_EVENTS.BOMB_MOVED,
		callback,
	)

	return () => {
		socket.off(
			GAME_EVENTS.BOMB_MOVED,
			callback,
		)
	}
}

export function onBombExploded(
	callback: (data: unknown) => void,
): () => void {

	const socket = getSocket()

	socket.on(
		GAME_EVENTS.BOMB_EXPLODED,
		callback,
	)

	return () => {
		socket.off(
			GAME_EVENTS.BOMB_EXPLODED,
			callback,
		)
	}
}

/*----------------------------POWER UPS----------------------------*/

export function onPowerUpPicked(
	callback: (data: unknown) => void,
): () => void {

	const socket = getSocket()

	socket.on(
		GAME_EVENTS.POWERUP_PICKED,
		callback,
	)

	return () => {
		socket.off(
			GAME_EVENTS.POWERUP_PICKED,
			callback,
		)
	}
}

/*----------------------------END GAME----------------------------*/

export function onGameEnded(
	callback: (data: GameEndedPayload) => void,
): () => void {
	const socket = getSocket()
	const handler = (data: GameEndedPayload) => {
		callback(data)
	}
	socket.on(
		GAME_EVENTS.GAME_ENDED,
		handler,
	)
	return () => {
		socket.off(
			GAME_EVENTS.GAME_ENDED,
			handler,
		)
	}
}