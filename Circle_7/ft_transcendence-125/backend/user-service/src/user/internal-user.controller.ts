import {
    Controller,
    Headers,
    Post,
    Body,
    UnauthorizedException,
} from '@nestjs/common';
import { GameResultDto } from './dto/game-result.dto';
import { UserService } from './user.service';

@Controller('internal/users')
export class InternalUserController {
    constructor(private readonly userService: UserService) {}

    @Post('game-result')
    recordGameResult(
        @Body() data: GameResultDto,
        @Headers('x-internal-service-key') serviceKey: string,
    ) {
        if (!process.env.GAME_SERVICE_INTERNAL_KEY ||
            serviceKey !== process.env.GAME_SERVICE_INTERNAL_KEY) {
            throw new UnauthorizedException();
        }

        return this.userService.recordGameResult(
            data.userId,
            data.result,
            data.bombplaced,
            data.enemyKill,
            data.xp,
        );
    }
}