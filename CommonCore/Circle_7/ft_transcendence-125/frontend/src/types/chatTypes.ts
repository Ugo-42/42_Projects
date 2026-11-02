export type ChatConversationType =
	| "private"
	| "lobby"

export type ChatMessage = {
	room: string
	userId: number
	username: string
	message: string
	date: string
}

export type ChatConversation = {
	id: string
	room: string
	type: ChatConversationType
	name: string

	friendId?: number
	lobbyId?: string
	avatarUrl?: string | null
}

export type ChatHistoryPayload = {
	room: string
	messages: ChatMessage[]
}

export type ChatJoinResponse = {
	success: boolean
	room?: string
	error?: string
	online?: boolean
}

export type ChatMessageResponse = {
	success: boolean
	error?: string
}

export type ChatTypingPayload = {
	userId: number
}