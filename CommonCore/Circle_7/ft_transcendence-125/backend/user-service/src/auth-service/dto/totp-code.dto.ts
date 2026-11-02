import { IsNotEmpty, IsString, Matches } from 'class-validator';

export class TotpCodeDto {
  @IsString()
  @IsNotEmpty()
  @Matches(/^\d{6}$/, { message: 'Code must contain 6 digits' })
  code: string;
}
