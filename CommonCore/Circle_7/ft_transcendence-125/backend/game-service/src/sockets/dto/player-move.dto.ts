import {
	IsInt,
	IsUUID,
	Max,
	Min,
} from 'class-validator'

export class PlayerMoveDto {

	@IsUUID()
	gameId!: string

	@IsInt()
	@Min(-1)
	@Max(1)
	dirX!: number

	@IsInt()
	@Min(-1)
	@Max(1)
	dirY!: number
}