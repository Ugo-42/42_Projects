import {
    IsNotEmpty,
    IsString,
} from 'class-validator';

export class JoinLobbyCodeDto
{
    @IsString()
    @IsNotEmpty()
    code: string;
}