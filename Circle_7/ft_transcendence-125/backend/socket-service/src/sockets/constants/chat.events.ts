export const CHAT_EVENTS = {
	JOIN: 'chat:join_room',
	JOIN_PRIVATE: 'chat:join_private',
	LEAVE: 'chat:leave_room',

	MESSAGE: 'chat:message',
	RECEIVED: 'chat:received',
	HISTORY: 'chat:history',

	TYPING: 'chat:typing',
	STOP_TYPING: 'chat:stop_typing',
} as const;