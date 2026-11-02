import {
	useCallback,
	useEffect,
	useMemo,
	useRef,
	useState,
} from "react"

import {connectSocket, getChatSocket, getAppSocket} from "@/services/socketService"
import {getFriends,} from "@/services/friendsService"
import {useChatContext,} from "@/contexts/ChatContext"
import {useAuth,} from "@/hooks/useAuth"
import type {Friend,} from "@/types/friendsTypes"

import type {
	ChatConversation,
	ChatHistoryPayload,
	ChatJoinResponse,
	ChatMessage,
	ChatMessageResponse,
} from "@/types/chatTypes"


export function useChat() {

	const {
		isOpen,
		setIsOpen,
		activeConversation,
		setActiveConversation,
		conversations,
		setConversations,
		messagesByRoom,
		setMessagesByRoom,
		unreadByRoom,
		setUnreadByRoom,
	} = useChatContext()
	const {user,} = useAuth()
	const lastReadStorageKey = user
		? `chatLastRead:${user.id}`
		: null
	const [loading,setLoading,] = useState(true)
	const [error,setError,] = useState<string | null>(null)
	const isOpenRef = useRef(isOpen)
	const activeConversationRef = useRef(activeConversation)
	const joinedPrivateRoomsRef = useRef<Set<string>>(new Set())

	const getLastReadByRoom =
		useCallback((): Record<string, string> => {
			if (!lastReadStorageKey)
				return {}
			const stored = localStorage.getItem(lastReadStorageKey)
			if (!stored)
				return {}
			try {
				return JSON.parse(stored)
			} catch {
				return {}
			}
		}, [lastReadStorageKey,])

	const setRoomLastRead =
		useCallback((room: string, date: string,
		) => {
			if (!lastReadStorageKey)
				return
			const current = getLastReadByRoom()
			current[room] = date
			localStorage.setItem(
				lastReadStorageKey,
				JSON.stringify(current))
		}, [lastReadStorageKey, getLastReadByRoom])

	const messages = useMemo(() => {
		if (!activeConversation)
			return []
		return (
			messagesByRoom[
				activeConversation.room
			] ?? []
		)
	}, [
		activeConversation,
		messagesByRoom,
	])

	const getPrivateRoom = useCallback((
		firstUserId: number,
		secondUserId: number,
	) => {
		const ids = [
			firstUserId,
			secondUserId,
		].sort(
			(left, right) =>
				left - right,
		)
		return `private:${ids[0]}:${ids[1]}`
	}, [])


	const buildPrivateConversation =
		useCallback((
			friend: Friend,
		): ChatConversation | null => {
			if (!user)
				return null
			const room = getPrivateRoom(
				user.id,
				friend.id,
			)
			return {
				id: room,
				room,
				type: "private",
				name: friend.username,
				friendId: friend.id,
				avatarUrl: friend.avatarUrl,
			}
		}, [
			user,
			getPrivateRoom,
		])


	const refreshConversations =
		useCallback(async () => {
			if (!user) {
				setConversations([])
				setLoading(false)
				return
			}
			try {
				setLoading(true)
				setError(null)
				const friends =
					await getFriends()

				const privateConversations =
					friends
						.map(
							buildPrivateConversation,
						)
						.filter(
							(
								conversation,
							): conversation is ChatConversation =>
								conversation !== null,
						)

				const nextConversations:
					ChatConversation[] = [
						...privateConversations,
					]
				const lobbyId =
					sessionStorage.getItem(
						"currentLobbyId",
					)
				const lobbyName =
					sessionStorage.getItem(
						"currentLobbyName",
					)
				if (lobbyId) {
					nextConversations.unshift({
						id: `lobby:${lobbyId}`,
						room: `lobby:${lobbyId}`,
						type: "lobby",
						name:
							lobbyName ||
							"Lobby",
						lobbyId,
					})
				}
				setConversations(
					nextConversations,
				)
			} catch (err) {
				console.error(
					"[CHAT] Failed to load conversations:",
					err,
				)
				setError(
					"Failed to load conversations",
				)
			} finally {
				setLoading(false)
			}
		}, [
			user,
			buildPrivateConversation,
			setConversations,
		])


	const openPrivateChat =
		useCallback((
			friend: Friend,
		) => {
			if (!user)
				return
			connectSocket()
			const socket =
				getChatSocket()
			if (!socket) {
				setError(
					"Chat socket unavailable",
				)
				return
			}
			const conversation =
				buildPrivateConversation(
					friend,
				)
			if (!conversation)
				return
			socket.emit(
				"chat:join_private",
				{
					userId: friend.id,
				},
				(
					response:
						ChatJoinResponse,
				) => {
					if (
						!response?.success
					) {
						console.error(
							"[CHAT] Failed to join private chat:",
							response?.error,
						)
						setError(
							response?.error ||
							"Unable to open chat",
						)
						return
					}
					setError(null)
					setUnreadByRoom((previous) => ({
						...previous,
						[conversation.room]: 0,
					}))
					setActiveConversation(conversation)
					setIsOpen(true)
				},
			)
		}, [
			user,
			buildPrivateConversation,
			setActiveConversation,
			setIsOpen,
		])


	const openLobbyChat =
		useCallback((
			lobbyId: string,
			lobbyName = "Lobby",
		) => {
			connectSocket()
			const socket =
				getChatSocket()
			if (!socket) {
				setError(
					"Chat socket unavailable",
				)
				return
			}
			const room =
				`lobby:${lobbyId}`
			const conversation:
				ChatConversation = {
					id: room,
					room,
					type: "lobby",
					name: lobbyName,
					lobbyId,
				}
			socket.emit(
				"chat:join_room",
				`lobby:${lobbyId}`,
				(
					response:
						ChatJoinResponse,
				) => {
					if (
						!response?.success
					) {
						console.error(
							"[CHAT] Failed to join lobby chat:",
							response?.error,
						)
						setError(
							response?.error ||
							"Unable to open lobby chat",
						)
						return
					}
					setError(null)
					setUnreadByRoom((previous) => ({
						...previous,
						[conversation.room]: 0,
					}))
					setActiveConversation(conversation)
					setIsOpen(true)
				},
			)
		}, [
			setActiveConversation,
			setIsOpen,
		])

	const leaveLobbyChat = useCallback(() => {
		const lobbyId = sessionStorage.getItem("currentLobbyId")
		if (!lobbyId)
			return
		const room = `lobby:${lobbyId}`
		const socket = getChatSocket()
		if (socket)
			socket.emit("chat:leave_room", room)
		if (activeConversation?.room === room)
			setActiveConversation(null)
		setConversations(
			conversations.filter(
				(conversation) => conversation.room !== room
			),
		)
		sessionStorage.removeItem("currentLobbyId")
		sessionStorage.removeItem("currentLobbyName")
	}, [
		activeConversation,
		conversations,
		setActiveConversation,
		setConversations,
	])

	const openConversation =
		useCallback((conversation: ChatConversation,
		) => {
			setUnreadByRoom((previous) => ({
				...previous,
				[conversation.room]: 0,
			}))
			if (conversation.type === "lobby") {
				if (conversation.lobbyId) {
					openLobbyChat(
						conversation.lobbyId,
						conversation.name,
					)
				}
				return
			}
			if (conversation.friendId === undefined) {
				return
			}
			const friend: Friend = {
				id: conversation.friendId,
				username: conversation.name,
				avatarUrl: conversation.avatarUrl,
			}
			openPrivateChat(friend)
		}, [
			openLobbyChat,
			openPrivateChat,
			setUnreadByRoom,
		])


	const sendMessage =
		useCallback((
			value: string,
		) => {
			if (!activeConversation)
				return
			const message =
				value.trim()
			if (!message)
				return
			const socket =
				getChatSocket()
			if (!socket) {
				setError(
					"Chat socket unavailable",
				)
				return
			}

			socket.emit(
				"chat:message",
				{
					room:
						activeConversation.room,
					message,
				},
				(
					response:
						ChatMessageResponse,
				) => {
					if (
						!response?.success
					) {
						console.error(
							"[CHAT] Failed to send message:",
							response?.error,
						)
						setError(
							response?.error ||
							"Unable to send message",
						)
						return
					}
					setError(null)
				},
			)
		}, [
			activeConversation,
		])

	const subscribeToChatRooms =
		useCallback(async () => {
			const socket = getChatSocket()
			if (!socket?.connected)
				return
			try {
				const friends =
					await getFriends()
				for (const friend of friends) {
					socket.emit(
						"chat:join_private",
						{userId: friend.id},
						(response: {
							success: boolean
							room?: string
						}) => {
							if (response?.success && response.room) {
								joinedPrivateRoomsRef.current.add(response.room)
							}
						},
					)
				}
				const lobbyId =
					sessionStorage.getItem(
						"currentLobbyId",
					)
				if (lobbyId) {
					socket.emit(
						"chat:join_room",
						`lobby:${lobbyId}`,
					)
				}
			} catch (error) {
				console.error(
					"[CHAT] Failed to subscribe to rooms:",
					error,
				)
			}
	}, [])

	const closeConversation =
		useCallback(() => {
			setActiveConversation(null)
		}, [
			setActiveConversation,
		])


	const toggleChat =
		useCallback(() => {
			setIsOpen(!isOpen)
		}, [
			isOpen,
			setIsOpen,
		])


	const closeChat =
		useCallback(() => {
			setIsOpen(false)
		}, [
			setIsOpen,])


	useEffect(() => {
		if (!user)
			return

		connectSocket()

		const socket = getChatSocket()
		if (!socket)
			return

		const handleHistory = (
			payload: ChatHistoryPayload,
		) => {
			setMessagesByRoom(
				(previous) => ({
					...previous,
					[payload.room]:
						payload.messages,
				}),
			)
			const lastReadByRoom = getLastReadByRoom()
			const lastRead = lastReadByRoom[payload.room]
			if (!lastRead) {
				const lastMessage =
					payload.messages[payload.messages.length - 1]
				if (lastMessage) {
					setRoomLastRead(payload.room, lastMessage.date)
				}
				return
			}
			const unreadCount = payload.messages.filter(
					(message) => {
						if (message.userId === user.id)
							return false
						return (new Date(message.date).getTime()
							> new Date(lastRead).getTime())
					},).length
			setUnreadByRoom(
				(previous) => ({
					...previous,
					[payload.room]: unreadCount,}),
			)
		}

		const handleMessage = (message: ChatMessage) => {
			setMessagesByRoom((previous) => ({
				...previous,
				[message.room]: [
					...(previous[message.room] ?? []),
					message,
				],
			}))
			if (message.userId === user.id) {
				setRoomLastRead(message.room, message.date)
				return
			}
			const isCurrentRoom = isOpenRef.current &&
				activeConversationRef.current?.room === message.room
			if (isCurrentRoom) {
				setRoomLastRead(message.room, message.date,)
				return
			}
			setUnreadByRoom((previous) => ({
				...previous,
				[message.room]:
					(previous[message.room] ?? 0) + 1,
			}))
		}

		const handleConnect = () => {void subscribeToChatRooms()}
		const handleDisconnect = () => {joinedPrivateRoomsRef.current.clear()}
		if (socket.connected)
			void subscribeToChatRooms()
		socket.on("connect", handleConnect)
		socket.on("chat:history", handleHistory)
		socket.on("chat:received", handleMessage)
		socket.on("disconnect", handleDisconnect)
		return () => {
			socket.off("connect", handleConnect)
			socket.off("chat:history", handleHistory)
			socket.off("chat:received", handleMessage)
			socket.off("disconnect", handleDisconnect)
		}
	}, [
		user,
		subscribeToChatRooms,	
		setMessagesByRoom,
		setUnreadByRoom,
		getLastReadByRoom,
		setRoomLastRead,
	])

	useEffect(() => {
		joinedPrivateRoomsRef.current.clear()
	}, [user?.id])

	useEffect(() => {
		void refreshConversations()
	}, [
		refreshConversations,
	])

	useEffect(() => {
		isOpenRef.current = isOpen
	}, [isOpen])

	useEffect(() => {
		activeConversationRef.current =
			activeConversation
	}, [activeConversation])

	useEffect(() => {
		if (!isOpen)
			return
		if (!activeConversation)
			return
		setUnreadByRoom((previous) => ({
			...previous,
			[activeConversation.room]: 0,
		}))
		const roomMessages = messagesByRoom[
				activeConversation.room] ?? []
		const lastMessage = roomMessages[
				roomMessages.length - 1]
		if (lastMessage) {
			setRoomLastRead(activeConversation.room, lastMessage.date,)
		}
	}, [
		isOpen,
		activeConversation,
		messagesByRoom,
		setUnreadByRoom,
		setRoomLastRead,
	])

	useEffect(() => {
		const socket = getChatSocket()
		if (!socket?.connected)
			return
		for (const conversation of conversations) {
			if (
				conversation.type !== "private" ||
				conversation.friendId === undefined
			)
				continue
			if (
				joinedPrivateRoomsRef.current.has(
					conversation.room,
				)
			)
				continue
			socket.emit(
				"chat:join_private",
				{userId: conversation.friendId},
				(response: {success: boolean}) => {
					if (!response?.success)
						return
					joinedPrivateRoomsRef.current.add(
						conversation.room,
					)
				},
			)
		}
	}, [conversations])

	useEffect(() => {
		if (!user)
			return
		connectSocket()
		const appSocket = getAppSocket()
		const chatSocket = getChatSocket()
		if (!appSocket || !chatSocket)
			return

		const handleFriendAccepted = (
			friend: {
				id: number
				username: string
				avatarUrl: string | null
			},
		) => {
			chatSocket.emit(
				"chat:join_private",
				{userId: friend.id},
				(response: {success: boolean
						room?: string
				}) => {
					if (response?.success && response.room) {
						joinedPrivateRoomsRef.current.add(response.room)
					}
				},
			)
			void refreshConversations()
		}

		appSocket.on("friend:accepted", handleFriendAccepted,)
		return () => {
			appSocket.off("friend:accepted", handleFriendAccepted)
		}
	}, [user, refreshConversations])


	return {
		isOpen,
		activeConversation,
		conversations,
		messages,
		loading,
		error,

		toggleChat,
		closeChat,
		closeConversation,
		openConversation,
		openPrivateChat,
		openLobbyChat,
		leaveLobbyChat,
		sendMessage,
		refreshConversations,
		unreadByRoom,
	}
}