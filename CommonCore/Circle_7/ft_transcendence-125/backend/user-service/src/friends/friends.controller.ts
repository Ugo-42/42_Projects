import {
    Controller,
    Delete,
    Get,
    Param,
    ParseIntPipe,
    Patch,
    Post,
    Req,
    UseGuards,
} from '@nestjs/common';

import { FriendsService } from './friends.service';
import { JwtAuthGuard } from '../auth-service/jwt-auth.guard';

@Controller('friends')
@UseGuards(JwtAuthGuard)
export class FriendsController {
    constructor(
        private readonly friendsService: FriendsService,
    ) {}

    @Post('request/:userId')
    sendRequest(
        @Req() req: any,
        @Param('userId', ParseIntPipe) userId: number,
    ) {
        return this.friendsService.sendRequest(
            Number(req.user.sub),
            userId,
        );
    }

    @Get('requests')
    getReceivedRequests(@Req() req: any) {
        return this.friendsService.getReceivedRequests(
            Number(req.user.sub),
        );
    }

    @Patch('requests/:id/accept')
    acceptRequest(
        @Req() req: any,
        @Param('id', ParseIntPipe) friendshipId: number,
    ) {
        return this.friendsService.acceptRequest(
            Number(req.user.sub),
            friendshipId,
        );
    }

    @Patch('requests/:id/decline')
    declineRequest(
        @Req() req: any,
        @Param('id', ParseIntPipe) friendshipId: number,
    ) {
        return this.friendsService.declineRequest(
            Number(req.user.sub),
            friendshipId,
        );
    }

    @Get()
    getFriends(@Req() req: any) {
        return this.friendsService.getFriends(
            Number(req.user.sub),
        );
    }

    @Get(':userId/status')
    areFriends(
        @Req() req: any,
        @Param('userId', ParseIntPipe) userId: number,
    ) {
        return this.friendsService.areFriends(
            Number(req.user.sub),
            userId,
        );
    }

    @Delete(':userId')
    removeFriend(
        @Req() req: any,
        @Param('userId', ParseIntPipe) userId: number,
    ) {
        return this.friendsService.removeFriend(
            Number(req.user.sub),
            userId,
        );
    }
}