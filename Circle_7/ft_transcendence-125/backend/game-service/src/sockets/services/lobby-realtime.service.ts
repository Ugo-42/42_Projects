import { Injectable } from '@nestjs/common'

import { LOBBY_EVENTS } from '../constants/lobby.events'
import { getLobbyRoom } from '../constants/room-names'
import { GameGateway } from '../gateway/game.gateway'

@Injectable()
export class LobbyRealtimeService {

	constructor(
		private readonly gameGateway: GameGateway,
	) {}


	lobbyUpdated(
		lobbyId: string,
	) {
		this.gameGateway.server
			.to(getLobbyRoom(lobbyId))
			.emit(
				LOBBY_EVENTS.UPDATED,
				{
					lobbyId,
				},
			)
	}


	lobbyStarted(
		lobbyId: string,
		gameId: string,
	) {
		this.gameGateway.server
			.to(getLobbyRoom(lobbyId))
			.emit(
				LOBBY_EVENTS.STARTED,
				{
					lobbyId,
					gameId,
				},
			)
	}


	lobbyClosed(
		lobbyId: string,
	) {
		this.gameGateway.server
			.to(getLobbyRoom(lobbyId))
			.emit(
				LOBBY_EVENTS.CLOSED,
				{
					lobbyId,
				},
			)
	}
}