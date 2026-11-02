export const APP_EVENTS = {
	// Présence
	USER_ONLINE: 'user:online',
	USER_OFFLINE: 'user:offline',
	PRESENCE_GET: 'presence:get',

	// Rooms générales
	JOIN_ROOM: 'join_room',
	LEAVE_ROOM: 'leave_room',

	// Friends 
	FRIEND_REQUEST: 'friend:request',
	FRIEND_ACCEPTED: 'friend:accepted',
	FRIEND_REMOVED: 'friend:removed',

	// Invitations
	GAME_INVITE: 'game:invite',
	GAME_INVITE_ACCEPT: 'game:invite:accept',
	GAME_INVITE_DECLINE: 'game:invite:decline',

	// Notifications
	NOTIFICATION: 'notification',
} as const;