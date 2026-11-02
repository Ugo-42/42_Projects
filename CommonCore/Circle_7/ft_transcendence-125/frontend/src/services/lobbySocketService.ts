import type { Socket } from "socket.io-client"

import {
	connectSocket,
	getGameSocket,
} from "@/services/socketService"

import { LOBBY_EVENTS } from "@/services/lobby.events"


type LobbyRoomPayload = {
	lobbyId: string
}


export type LobbyRoomAck =
	| {
		success: true
		lobbyId: string
	}
	| {
		success: false
		error: string
	}


function getSocket(): Socket {

	const socket =
		getGameSocket() ?? connectSocket()

	if (!socket) {
		throw new Error(
			"LOBBY_SOCKET_UNAVAILABLE",
		)
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
	event: typeof LOBBY_EVENTS.JOIN
		| typeof LOBBY_EVENTS.LEAVE,
	lobbyId: string,
): Promise<LobbyRoomAck> {

	const socket = getSocket()

	await waitForConnection(socket)

	const payload: LobbyRoomPayload = {
		lobbyId,
	}

	return socket
		.timeout(5000)
		.emitWithAck(
			event,
			payload,
		)
}


export async function joinLobbyRoom(
	lobbyId: string,
): Promise<LobbyRoomAck> {

	return emitRoomEvent(
		LOBBY_EVENTS.JOIN,
		lobbyId,
	)
}


export async function leaveLobbyRoom(
	lobbyId: string,
): Promise<LobbyRoomAck> {

	return emitRoomEvent(
		LOBBY_EVENTS.LEAVE,
		lobbyId,
	)
}