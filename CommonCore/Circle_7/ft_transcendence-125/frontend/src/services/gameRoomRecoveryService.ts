import type { Socket } from "socket.io-client"

import { GAME_EVENTS } from "@/services/game.events"
import { LOBBY_EVENTS } from "@/services/lobby.events"


type RoomAck = {
	success: boolean
	error?: string
}


async function restoreLobbyRoom(
	socket: Socket,
	lobbyId: string,
) {

	try {
		const result =
			await socket
				.timeout(5000)
				.emitWithAck(
					LOBBY_EVENTS.JOIN,
					{
						lobbyId,
					},
				) as RoomAck
		if (!result.success) {
			console.warn(
				"[SOCKET RECOVERY] Failed to restore lobby room:",
				result.error,
			)
			return
		}
		console.log(`[SOCKET RECOVERY] Restored lobby room ${lobbyId}`)

	} catch (error) {
		console.error(
			"[SOCKET RECOVERY] Failed to restore lobby room:",
			error,
		)
	}
}


async function restoreGameRoom(
	socket: Socket,
	gameId: string,
) {

	try {
		const result =
			await socket
				.timeout(5000)
				.emitWithAck(
					GAME_EVENTS.JOIN,
					{
						gameId,
					},
				) as RoomAck

		if (!result.success) {
			console.warn(
				"[SOCKET RECOVERY] Failed to restore game room:",
				result.error,
			)
			return
		}
		console.log(`[SOCKET RECOVERY] Restored game room ${gameId}`)

	} catch (error) {
		console.error(
			"[SOCKET RECOVERY] Failed to restore game room:",
			error,
		)
	}
}


export async function restoreGameSocketRooms(
	socket: Socket,
) {
	const lobbyId = sessionStorage.getItem("currentLobbyId")
	const gameId = sessionStorage.getItem("currentGameId")
	const inGame = sessionStorage.getItem("inGame") === "true"

	if (lobbyId) {
		await restoreLobbyRoom(
			socket,
			lobbyId,
		)
	}

	if (inGame && gameId) {
		await restoreGameRoom(
			socket,
			gameId,
		)
	}
}