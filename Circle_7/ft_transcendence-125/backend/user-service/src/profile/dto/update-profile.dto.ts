import {
    IsOptional,
    IsString,
    MaxLength,
} from 'class-validator';

export class UpdateProfileDto {
    @IsOptional()
    @IsString()
    @MaxLength(200)
    bio?: string;

    @IsOptional()
    @IsString()
    avatarUrl?: string;
}