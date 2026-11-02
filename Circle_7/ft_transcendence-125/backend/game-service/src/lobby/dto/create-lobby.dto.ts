import {
	IsBoolean,
	IsNotEmpty,
	IsString,
	MaxLength,
} from 'class-validator';

export class CreateLobbyDto
{
	@IsString()
	@IsNotEmpty()
	@MaxLength(50)
	name: string;

	@IsBoolean()
	isPrivate: boolean;
}