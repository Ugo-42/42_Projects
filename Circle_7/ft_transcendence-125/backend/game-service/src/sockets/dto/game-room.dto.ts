import { IsUUID } from 'class-validator'

export class GameRoomDto {

	@IsUUID()
	gameId!: string
}