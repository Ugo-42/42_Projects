export const WS_EVENTS = {
	// Rooms
	JOIN_ROOM: 'join_room',
	LEAVE_ROOM: 'leave_room',

	// Presence
	USER_ONLINE: 'user:online',
	USER_OFFLINE: 'user:offline',

	// Jeu
	GAME_START: 'game:start',
	PLAYER_MOVE: 'player:move',
	GAME_UPDATE: 'game:update',

	// Chat
	CHAT_MESSAGE: 'chat:message',
	CHAT_RECEIVED: 'chat:received',
} as const;
