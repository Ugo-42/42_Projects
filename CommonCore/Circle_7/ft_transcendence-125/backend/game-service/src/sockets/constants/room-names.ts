export function getLobbyRoom(
	lobbyId: string,
) {
	return `lobby:${lobbyId}`
}

export function getGameRoom(
	gameId: string,
) {
	return `game:${gameId}`
}