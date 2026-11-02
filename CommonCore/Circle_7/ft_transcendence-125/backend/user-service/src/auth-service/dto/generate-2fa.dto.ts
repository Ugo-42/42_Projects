import { IsOptional, IsString } from 'class-validator';

export class GenerateTwoFactorDto {
  @IsString()
  @IsOptional()
  appName?: string;
}
