import {
	useCallback,
	useEffect,
	useState,
} from "react"

import { useNavigate } from "react-router-dom"

import {
	getLobby,
	leaveLobby,
	setLobbyReady,
	setLobbyColor,
	startLobbyGame,
} from "@/services/lobbyService"

import {
	connectSocket,
	getChatSocket,
	getGameSocket,
} from "@/services/socketService"

import {
	joinLobbyRoom,
	leaveLobbyRoom,
} from "@/services/lobbySocketService"

import { LOBBY_EVENTS } from "@/services/lobby.events"

import type { Lobby } from "@/types/lobby"
import { useChatContext } from "@/contexts/ChatContext"



export function useLobby(lobbyId?: string) {

	const navigate = useNavigate()
	const [lobby, setLobby] =
		useState<Lobby | null>(null)
	const [loading, setLoading] =
		useState(true)
	const [error, setError] =
		useState<string | null>(null)
	const [leaving, setLeaving] =
		useState(false)
	const { removeConversation } = useChatContext()


	const loadLobby = useCallback(async () => {

		if (!lobbyId) {
			setError("Invalid lobby id")
			setLoading(false)
			return
		}
		try {
			setLoading(true)
			setError(null)
			const result =
				await getLobby(lobbyId)
			setLobby(result)
		} catch (error) {
			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to load lobby")
			}
		} finally {
			setLoading(false)
		}
	}, [lobbyId])


	/*----------------------------LOAD LOBBY----------------------------*/

	useEffect(() => {
		void loadLobby()
	}, [loadLobby])


	/*----------------------------CONNECT LOBBY----------------------------*/

	useEffect(() => {

		if (!lobbyId)
			return

		const joinRoom = async () => {

			try {
				const result = await joinLobbyRoom(
						lobbyId)
				if (!result.success) {
					console.error(
						"[LOBBY SOCKET] Failed to join room:",
						result.error,
					)
				}
			} catch (error) {
				console.error(
					"[LOBBY SOCKET] Failed to join room:",
					error,
				)
			}
		}
		void joinRoom()
	}, [lobbyId])

	/*----------------------------CONNECT LOBBY CHAT----------------------------*/

	useEffect(() => {
		if (!lobbyId)
			return
		connectSocket()
		const chatSocket =
			getChatSocket()
		if (!chatSocket)
			return
		const joinChatRoom = () => {
			chatSocket.emit(
				"chat:join_room",
				`lobby:${lobbyId}`,
			)
		}
		if (chatSocket.connected) {
			joinChatRoom()
		} else {
			chatSocket.once(
				"connect",
				joinChatRoom,
			)
		}
		return () => {
			chatSocket.off(
				"connect",
				joinChatRoom,
			)
		}
	}, [lobbyId])


	/*----------------------------UPDATE LOBBY----------------------------*/

	useEffect(() => {

		if (!lobbyId)
			return
		const socket =
			getGameSocket() ?? connectSocket()
		if (!socket)
			return
		const handleLobbyUpdated = (
			payload: {
				lobbyId: string
			},
		) => {
			if (payload.lobbyId !== lobbyId)
				return

			void loadLobby()
		}
		socket.on(
			LOBBY_EVENTS.UPDATED,
			handleLobbyUpdated,
		)
		return () => {
			socket.off(
				LOBBY_EVENTS.UPDATED,
				handleLobbyUpdated,
			)
		}
	}, [lobbyId, loadLobby])


	/*----------------------------LOBBY CLOSE----------------------------*/

	useEffect(() => {

		if (!lobbyId)
			return

		const socket = getGameSocket() ?? connectSocket()

		if (!socket)
			return

		const handleLobbyClosed = (
			payload: {
				lobbyId: string
			},
		) => {
			if (payload.lobbyId !== lobbyId) {
				return
			}
			const chatSocket = getChatSocket()

			if (chatSocket) {
				chatSocket.emit(
					"chat:leave_room",
					`lobby:${lobbyId}`,
				)
			}

			void leaveLobbyRoom(
				lobbyId
			).catch((error) => {
				console.error(
					"[LOBBY SOCKET] Failed to leave closed lobby room:",
					error,
				)
			})

			removeConversation(`lobby:${lobbyId}`)
			sessionStorage.removeItem("currentLobbyId")
			sessionStorage.removeItem("currentLobbyName")
			navigate("/selection",{
					replace: true,
				})
		}
		socket.on(
			LOBBY_EVENTS.CLOSED,
			handleLobbyClosed,
		)
		return () => {
			socket.off(
				LOBBY_EVENTS.CLOSED,
				handleLobbyClosed,
			)
		}

	}, [
		lobbyId,
		navigate,
		removeConversation,
	])


	/*----------------------------GAME START EFFECT----------------------------*/

	useEffect(() => {

		if (!lobbyId)
			return

		const socket = getGameSocket() ?? connectSocket()

		if (!socket)
			return

		const handleLobbyStarted = (
			payload: {
				lobbyId: string
				gameId: string
			},
		) => {
			if (payload.lobbyId !== lobbyId) {
				return
			}
			sessionStorage.setItem("currentGameId", payload.gameId)
			sessionStorage.setItem("inGame", "true")
			navigate("/game")
		}

		socket.on(
			LOBBY_EVENTS.STARTED,
			handleLobbyStarted,
		)
		return () => {
			socket.off(
				LOBBY_EVENTS.STARTED,
				handleLobbyStarted,
			)
		}

	}, [lobbyId, navigate])

	/*----------------------------PLAYER LEAVE----------------------------*/

	const handleLeave = async () => {

		if (!lobbyId || leaving)
			return

		try {
			setLeaving(true)
			setError(null)

			await leaveLobby(lobbyId)

			try {
				await leaveLobbyRoom(
					lobbyId,
				)
			} catch (error) {
				console.error(
					"[LOBBY SOCKET] Failed to leave room:",
					error,
				)
			}

			const chatSocket = getChatSocket()

			if (chatSocket) {
				chatSocket.emit(
					"chat:leave_room",
					`lobby:${lobbyId}`
				)
			}
			removeConversation(`lobby:${lobbyId}`)
			sessionStorage.removeItem("currentLobbyId")
			sessionStorage.removeItem("currentLobbyName")
			navigate(
				"/selection",
				{replace: true}
			)
		} catch (error) {
			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to leave lobby")
			}
		} finally {setLeaving(false)}
	}

	/*----------------------------PLAYER READY----------------------------*/

	const handleReady = async (
		ready: boolean,
	) => {

		if (!lobbyId)
			return

		try {
			setError(null)

			const updatedLobby =
				await setLobbyReady(
					lobbyId,
					ready,
				)
			setLobby(updatedLobby)

		} catch (error) {
			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to update ready status")
			}
		}
	}

	/*----------------------------PLAYER COLOR----------------------------*/

	const handleSetColor = async (
		color: string,
	) => {

		if (!lobbyId)
			return

		try {
			setError(null)

			const updatedLobby =
				await setLobbyColor(
					lobbyId,
					color,
			)
			setLobby(updatedLobby)

		} catch (error) {
			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to update color")
			}
		}
	}

	/*----------------------------GAME START----------------------------*/

	const handleStartGame = async () => {
		if (!lobbyId)
			return

		try {
			setError(null)

			const updatedLobby =
				await startLobbyGame(
					lobbyId,
				)
			setLobby(updatedLobby)

		} catch (error) {
			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to start game")
			}
		}
	}


	return {
		lobby,
		loading,
		error,
		leaving,
		loadLobby,
		handleLeave,
		handleReady,
		handleSetColor,
		handleStartGame,
	}
}
