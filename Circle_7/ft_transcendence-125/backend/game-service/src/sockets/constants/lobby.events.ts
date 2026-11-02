export const LOBBY_EVENTS = {
	// Client -> Server
	JOIN: 'lobby:join',
	LEAVE: 'lobby:leave',

	// Server -> Client
	UPDATED: 'lobby:updated',
	STARTED: 'lobby:started',
	CLOSED: 'lobby:closed',
} as const