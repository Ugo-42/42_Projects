import {
	Body,
	Controller,
	Get,
	Param,
	Patch,
	Post,
	UseGuards,
} from '@nestjs/common';

import { LobbyService } from './lobby.service';
import { CreateLobbyDto } from './dto/create-lobby.dto';
import { JoinLobbyCodeDto } from './dto/join-lobby-code.dto';
import { SetReadyDto } from './dto/set-ready.dto';
import { SetColorDto } from './dto/set-color.dto';
import { LobbyRealtimeService } from '../sockets/services/lobby-realtime.service'

import { JwtAuthGuard } from '../auth/jwt-auth.guard';
import { CurrentUser } from '../auth/current-user.decorator';
import type { JwtPayload } from '../auth/jwt-payload.type';

@UseGuards(JwtAuthGuard)
@Controller('/lobbies')
export class LobbyController
{
	constructor(
		private readonly lobbyService: LobbyService,
		private readonly lobbyRealtimeService: LobbyRealtimeService,
	) {}

	@Get()
	async getPublicLobbies()
	{
		return this.lobbyService.getPublicLobbies();
	}

	@Get(':id')
	async getLobby(
		@CurrentUser() user: JwtPayload,
		@Param('id') id: string,
	)
	{
		const userId = Number(user.sub);

		return this.lobbyService.getLobby(
			userId,
			id,
		);
	}

	@Post()
	async createLobby(
		@CurrentUser() user: JwtPayload,
		@Body() dto: CreateLobbyDto,
	)
	{
		const userId = Number(user.sub);

		return this.lobbyService.createLobby(
			userId,
			user.username,
			dto,
		);
	}

	@Post('join-by-code')
	async joinLobbyByCode(
		@CurrentUser() user: JwtPayload,
		@Body() dto: JoinLobbyCodeDto,
	)
	{
		const userId = Number(user.sub);

		const lobby = await this.lobbyService.joinLobbyByCode(
			userId,
			user.username,
			dto.code,
		);
		this.lobbyRealtimeService.lobbyUpdated(lobby.id);

		return lobby;
	}

	@Post('leave-current')
	async leaveCurrentLobby(
		@CurrentUser() user: JwtPayload,
	)
	{
		const userId = Number(user.sub)

		const result =
			await this.lobbyService.leaveCurrentLobby(
				userId,
			)

		if (
			result.left &&
			result.lobbyId
		) {
			if (result.deleted) {
				this.lobbyRealtimeService.lobbyClosed(
					result.lobbyId,
				)
			} else {
				this.lobbyRealtimeService.lobbyUpdated(
					result.lobbyId,
				)
			}
		}

		return result
	}

	@Post(':id/join')
	async joinPublicLobby(
		@CurrentUser() user: JwtPayload,
		@Param('id') id: string,
	)
	{
		const userId = Number(user.sub);

		const lobby = await this.lobbyService.joinPublicLobby(
			userId,
			user.username,
			id,
		);

		this.lobbyRealtimeService.lobbyUpdated(lobby.id);

		return lobby;
	}

	@Post(':id/leave')
	async leaveLobby(
		@CurrentUser() user: JwtPayload,
		@Param('id') id: string,
	)
	{
		const userId = Number(user.sub);

		const result = await this.lobbyService.leaveLobby(
			userId,
			id,
		);
		if (result.deleted) {
			this.lobbyRealtimeService.lobbyClosed(id);
		} else {
			this.lobbyRealtimeService.lobbyUpdated(id);
		}

		return result;
	}

	@Patch(':id/ready')
	async setReady(
		@CurrentUser() user: JwtPayload,
		@Param('id') id: string,
		@Body() dto: SetReadyDto,
	)
	{
		const userId = Number(user.sub);

		const lobby = await this.lobbyService.setReady(
			userId,
			id,
			dto.ready,
		);
		this.lobbyRealtimeService.lobbyUpdated(id);

		return lobby;
	}

	@Patch(':id/color')
	async setColor(
		@CurrentUser() user: JwtPayload,
		@Param('id') id: string,
		@Body() dto: SetColorDto,
	)
	{
		const userId = Number(user.sub);

		const lobby = await this.lobbyService.setColor(
			userId,
			id,
			dto.color,
		);
		this.lobbyRealtimeService.lobbyUpdated(id);

		return lobby;
	}

	@Post(':id/start')
	async startGame(
		@CurrentUser() user: JwtPayload,
		@Param('id') id: string,
	)
	{
		const userId = Number(user.sub);

		const lobby = await this.lobbyService.startGame(
			userId,
			id,
		);
		this.lobbyRealtimeService.lobbyStarted(id, lobby.gameId);

		return lobby;
	}
}
