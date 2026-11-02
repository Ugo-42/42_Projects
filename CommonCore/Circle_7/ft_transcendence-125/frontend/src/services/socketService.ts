import { io, Socket } from "socket.io-client"
import { restoreGameSocketRooms } from "@/services/gameRoomRecoveryService"

let gameSocket: Socket | null = null
let appSocket: Socket | null = null
let chatSocket: Socket | null = null

export function connectSocket() {
	console.log("[SOCKET] connectSockets called")

	const token = localStorage.getItem("token")

	if (!token) {
		console.error("[SOCKET] No authentication token found.")
		return null
	}

	if (!gameSocket) {
		gameSocket = io(`${window.location.origin}/game`, {
			path: "/game-socket.io",
			auth: {
				token,
			},
		})

		gameSocket.on(
			"connect",
			() => {
				console.log("[GAME SOCKET] connected:",
					gameSocket?.id,
				)
				if (!gameSocket)
					return
				void restoreGameSocketRooms(gameSocket)
			}
		)

		gameSocket.on("connect_error", (error) => {
			console.error(
				"[GAME SOCKET] connection error:",
				error,
			)
		})

		gameSocket.on("disconnect", (reason) => {
			console.log(
				"[GAME SOCKET] disconnected:",
				reason,
			)
		})
	}

	if (!appSocket) {
		appSocket = io(`${window.location.origin}/app`, {
			path: "/socket.io",
			auth: {
				token,
			},
		})

		appSocket.on("connect", () => {
			console.log(
				"[APP SOCKET] connected:",
				appSocket?.id,
			)
		})

		appSocket.on("connect_error", (error) => {
			console.error(
				"[APP SOCKET] connection error:",
				error,
			)
		})

		appSocket.on("disconnect", (reason) => {
			console.log(
				"[APP SOCKET] disconnected:",
				reason,
			)
		})
	}

	if (!chatSocket) {
		chatSocket = io(`${window.location.origin}/chat`, {
			path: "/socket.io",
			auth: {
				token,
			},
		})

		chatSocket.on("connect", () => {
			console.log(
				"[CHAT SOCKET] connected:",
				chatSocket?.id,
			)
		})

		chatSocket.on("connect_error", (error) => {
			console.error(
				"[CHAT SOCKET] connection error:",
				error,
			)
		})

		chatSocket.on("disconnect", (reason) => {
			console.log(
				"[CHAT SOCKET] disconnected:",
				reason,
			)
		})
	}

	return gameSocket
}

export function disconnectSockets() {
	if (gameSocket) {
		gameSocket.disconnect()
		gameSocket = null
	}

	if (appSocket) {
		appSocket.disconnect()
		appSocket = null
	}

	if (chatSocket) {
		chatSocket.disconnect()
		chatSocket = null
	}
}

export function getAppSocket() {
	return appSocket
}

export function getChatSocket() {
	return chatSocket
}

export function getGameSocket() {
	return gameSocket
}