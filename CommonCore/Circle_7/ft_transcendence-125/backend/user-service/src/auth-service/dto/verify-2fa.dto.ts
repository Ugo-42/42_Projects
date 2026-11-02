import { IsNotEmpty, IsString, Matches } from 'class-validator';

export class VerifyTwoFactorDto {
  @IsString()
  @IsNotEmpty()
  twoFactorToken: string;

  @IsString()
  @IsNotEmpty()
  @Matches(/^\d{6}$/, { message: 'Code must contain 6 digits' })
  code: string;
}
