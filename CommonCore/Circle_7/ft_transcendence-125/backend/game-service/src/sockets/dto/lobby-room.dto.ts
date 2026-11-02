import { IsUUID } from 'class-validator'

export class LobbyRoomDto {

	@IsUUID()
	lobbyId!: string
}