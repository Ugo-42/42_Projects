export const GAME_EVENTS = {
	// Client -> Server
	JOIN: "game:join",
	LEAVE: "game:leave",

	PLAYER_MOVE: "player:move",
	PLAYER_STOP: "player:stop",

	BOMB_PLACE: "bomb:place",

	// Server -> Client
	STATE: "game:state",

	PLAYER_MOVED: "player:moved",
	PLAYER_LEFT: "player:left",
	PLAYER_DEAD: "player:dead",

	BOMB_PLACED: "bomb:placed",
	BOMB_MOVED: "bomb:moved",
	BOMB_EXPLODED: "bomb:exploded",

	POWERUP_SPAWNED: "powerup:spawned",
	POWERUP_PICKED: "powerup:picked",

	GAME_ENDED: "game:ended",
} as const