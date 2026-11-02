import { IsIn, IsInt, Min } from 'class-validator';

export class GameResultDto {
    @IsInt()
    @Min(1)
    userId!: number;

    @IsIn(['win', 'loss', 'draw'])
    result!: 'win' | 'loss' | 'draw';

    @IsInt()
    @Min(0)
    bombplaced!: number;

    @IsInt()
    @Min(0)
    enemyKill!: number;

    @IsInt()
    @Min(0)
    xp!: number;
}