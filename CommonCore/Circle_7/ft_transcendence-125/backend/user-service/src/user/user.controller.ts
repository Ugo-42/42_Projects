import {
    Body,
    Controller,
    Delete,
    Get,
    Query,
    Param,
    ParseIntPipe,
    Patch,
    Req,
    UseGuards,
} from '@nestjs/common';

import { UserService } from './user.service';
import { UpdateUserDto } from './dto/update-user.dto';
import { JwtAuthGuard } from '../auth-service/jwt-auth.guard';

@Controller('users')
@UseGuards(JwtAuthGuard)
export class UserController {
    constructor(
        private readonly userService: UserService,
    ) {}

    @Get('me')
    getMe(@Req() req: any) {
        return this.userService.findById(Number(req.user.sub));
    }

    @Get('search')
    @UseGuards(JwtAuthGuard)
    searchUsers(
        @Req() req: any,
        @Query('username') username: string,
    ) {
        return this.userService.searchUsers(username, Number(req.user.sub));
    }

    @Get('leaderboard')
    getLeaderboard() {
        return this.userService.getLeaderboard();
    }

    @Get(':id')
    getUser(
        @Param('id', ParseIntPipe) id: number,
    ) {
        return this.userService.findById(id);
    }

    @Get('username/:username')
    getByUsername(
        @Param('username') username: string,
    ) {
        return this.userService.findByUsername(username);
    }

    @Patch('me')
    updateMe(
        @Req() req: any,
        @Body() data: UpdateUserDto,
    ) {
        return this.userService.updateUser(
            Number(req.user.sub),
            data,
        );
    }

    @Delete('me')
    deleteMe(@Req() req: any) {
        return this.userService.deleteUser(Number(req.user.sub));
    }
}