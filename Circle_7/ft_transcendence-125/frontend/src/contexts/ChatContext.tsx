import {
	createContext,
	useContext,
	useState,
	useEffect,
	type ReactNode,
} from "react"

import type {
	ChatConversation,
	ChatMessage,
} from "@/types/chatTypes"

import { useAuth } from "@/hooks/useAuth"

type MessagesByRoom = Record<string, ChatMessage[]>

type ChatContextType = {
	isOpen: boolean
	setIsOpen: (value: boolean) => void

	activeConversation: ChatConversation | null
	setActiveConversation: (
		conversation: ChatConversation | null
	) => void

	conversations: ChatConversation[]
	setConversations: (
		conversations: ChatConversation[]
	) => void

	messagesByRoom: MessagesByRoom
	setMessagesByRoom: (
		messages: MessagesByRoom
		| ((previous: MessagesByRoom) => MessagesByRoom)
	) => void

	unreadByRoom: Record<string, number>
	setUnreadByRoom: React.Dispatch<
		React.SetStateAction<Record<string, number>>
	>

	removeConversation: (room: string) => void
}

const ChatContext = createContext<ChatContextType | undefined>(
	undefined
)

type ChatProviderProps = {
	children: ReactNode
}

export function ChatProvider({
	children,
}: ChatProviderProps) {

	const { user } = useAuth()
	const [isOpen, setIsOpen] = useState(false)

	const [
		activeConversation,
		setActiveConversation,
	] = useState<ChatConversation | null>(null)

	const [
		conversations,
		setConversations,
	] = useState<ChatConversation[]>([])

	const [
		messagesByRoom,
		setMessagesByRoom,
	] = useState<MessagesByRoom>({})

	const [
		unreadByRoom,
		setUnreadByRoom,
	] = useState<Record<string, number>>({})

	const removeConversation = (room: string) => {
		setActiveConversation((previous) => {
			if (previous?.room === room)
				return null
			return previous
		})
		setConversations((previous) =>
			previous.filter(
				(conversation) => conversation.room !== room,
			),
		)
		setMessagesByRoom((previous) => {
			const next = {
				...previous,
			}
			delete next[room]
			return next
		})
		setUnreadByRoom((previous) => {
			const next = {...previous}
			delete next[room]
			return next
		})
	}

	useEffect(() => {
		setIsOpen(false)
		setActiveConversation(null)
		setConversations([])
		setMessagesByRoom({})
		if (!user) {
			setUnreadByRoom({})
			return
		}
		const stored = sessionStorage.getItem(`chatUnread:${user.id}`)
		if (!stored) {
			setUnreadByRoom({})
			return
		}
		try {
			setUnreadByRoom(
				JSON.parse(stored),
			)
		} catch {setUnreadByRoom({})}
	}, [user?.id])

	useEffect(() => {
		if (!user)
			return
		sessionStorage.setItem(
			`chatUnread:${user.id}`,
			JSON.stringify(unreadByRoom),
		)
	}, [unreadByRoom, user?.id])

	return (
		<ChatContext.Provider
			value={{
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
				removeConversation,
			}}
		>
			{children}
		</ChatContext.Provider>
	)
}

export function useChatContext() {

	const context = useContext(ChatContext)

	if (!context) {
		throw new Error(
			"useChatContext must be used inside ChatProvider"
		)
	}

	return context
}