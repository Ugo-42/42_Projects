import { IsIn, IsString } from 'class-validator';

export const AVAILABLE_COLORS = [
	'blue', 'cyan', 'green', 'orange', 'yellow', 'red', 'pink', 'purple',
] as const;

export class SetColorDto {
	@IsString()
	@IsIn(AVAILABLE_COLORS)
	color: string;
}
