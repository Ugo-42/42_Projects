import {
	BadRequestException,
	ConflictException,
	ForbiddenException,
	Injectable,
	NotFoundException,
	OnModuleDestroy, 
	OnModuleInit
} from '@nestjs/common';

import { PlayerColor } from '../game-logic/models/player';
import { PrismaService } from '../prisma/prisma.service';
import { CreateLobbyDto } from './dto/create-lobby.dto';
import { AVAILABLE_COLORS } from './dto/set-color.dto';
import { GameManagerService } from '../game-logic/game-manager.service';
import { GameEngineEventsService } from '../game-logic/services/game-engine-events.service'
import { LobbyRealtimeService } from '../sockets/services/lobby-realtime.service'
import { randomUUID } from 'crypto';

const POST_GAME_DELAY_MS = 5000

@Injectable()
export class LobbyService
	implements OnModuleInit, OnModuleDestroy
{
	private readonly postGameTimers = new Map<string, NodeJS.Timeout>()

	constructor(
		private readonly prisma: PrismaService,
		private readonly gameManagerService: GameManagerService,
		private readonly gameEngineEvents: GameEngineEventsService,
		private readonly lobbyRealtimeService: LobbyRealtimeService,
	) {}

	private unsubscribeGameEnded: (() => void) | null = null

	onModuleInit(): void {
		this.unsubscribeGameEnded =
			this.gameEngineEvents.onGameEnded(
				(payload) => {
					void this.handleGameEnded(
						payload.lobbyId,
					).catch((error) => {
						console.error(
							'[LOBBY] Failed to reset lobby after game end:',
							error,
						)
					})
				},
			)
	}

	onModuleDestroy(): void {
		this.unsubscribeGameEnded?.()
		this.unsubscribeGameEnded = null

		this.postGameTimers.forEach((time) => clearTimeout(time))
		this.postGameTimers.clear()
	}
	
	private async handleGameEnded(
		lobbyId: string,
	): Promise<void> {

		const lobby =
			await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
		})

		if (!lobby) {
			return
		}

		await this.prisma.lobbyPlayer.updateMany({
			where: {
				lobbyId,
			},
			data: {
				ready: false,
			},
		})

		this.lobbyRealtimeService.lobbyUpdated(
			lobbyId,
		)

		const previousTimer =
			this.postGameTimers.get(lobbyId)

		if (previousTimer) {
			clearTimeout(previousTimer)
		}

		const timer =
			setTimeout(() => {
			void this.finishPostGame(
				lobbyId,
			).catch((error) => {
				console.error(
					'[LOBBY] Failed to finish post-game state:',
					error,
				)
			})
		}, POST_GAME_DELAY_MS)

		this.postGameTimers.set(
			lobbyId,
			timer,
		)
	}

	private async finishPostGame(
		lobbyId: string,
	): Promise<void> {

		this.postGameTimers.delete(
			lobbyId,
		)

		const lobby =
			await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
		})

		if (!lobby) {
			return
		}

		if (lobby.status !== 'IN_GAME') {
			return
		}

		await this.prisma.lobby.update({
			where: {
				id: lobbyId,
			},
			data: {
				status: 'WAITING',
			},
		})

		this.lobbyRealtimeService.lobbyUpdated(
			lobbyId,
		)
	}

	async getPublicLobbies()
	{
		return this.prisma.lobby.findMany({
			where: {
				isPrivate: false,
				status: 'WAITING',
			},
			include: {
				players: true,
			},
			orderBy: {
				createdAt: 'desc',
			},
		});
	}

	async getLobby(
		userId: number,
		lobbyId: string,
	)
	{
		const lobby = await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		const isMember = lobby.players.some(
			(player) => player.userId === userId,
		);

		if (!isMember) {
			throw new ForbiddenException(
				'You are not a member of this lobby',
			);
		}

		return lobby;
	}

	async createLobby(
		userId: number,
		username: string,
		dto: CreateLobbyDto,
	)
	{
		await this.ensureUserIsNotInLobby(userId);

		const code = dto.isPrivate
			? await this.generateUniqueCode()
			: null;

		return this.prisma.lobby.create({
			data: {
				name: dto.name,
				ownerId: userId,
				isPrivate: dto.isPrivate,
				code,
				players: {
					create: {
						userId,
						username,
					},
				},
			},
			include: {
				players: true,
			},
		});
	}

	async joinPublicLobby(
		userId: number,
		username: string,
		lobbyId: string,
	)
	{
		await this.ensureUserIsNotInLobby(userId);

		const lobby = await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		if (lobby.isPrivate) {
			throw new ForbiddenException(
				'Cannot join a private lobby directly',
			);
		}

		if (lobby.status !== 'WAITING') {
			throw new ConflictException(
				'Lobby is not waiting for players',
			);
		}

		if (lobby.players.length >= lobby.maxPlayers) {
			throw new ConflictException('Lobby is full');
		}

		await this.prisma.lobbyPlayer.create({
			data: {
				lobbyId,
				userId,
				username,
			},
		});

		return this.getLobby(userId, lobbyId);
	}

	async joinLobbyByCode(
		userId: number,
		username: string,
		code: string,
	)
	{
		await this.ensureUserIsNotInLobby(userId);

		const normalizedCode = code.trim().toUpperCase();

		const lobby = await this.prisma.lobby.findUnique({
			where: {
				code: normalizedCode,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		if (!lobby.isPrivate) {
			throw new BadRequestException(
				'This code does not belong to a private lobby',
			);
		}

		if (lobby.status !== 'WAITING') {
			throw new ConflictException(
				'Lobby is not waiting for players',
			);
		}

		if (lobby.players.length >= lobby.maxPlayers) {
			throw new ConflictException('Lobby is full');
		}

		await this.prisma.lobbyPlayer.create({
			data: {
				lobbyId: lobby.id,
				userId,
				username,
			},
		});

		return this.getLobby(userId, lobby.id);
	}

	async leaveLobby(
		userId: number,
		lobbyId: string,
	)
	{
		const lobby = await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		const player = lobby.players.find(
			(player) => player.userId === userId,
		);

		if (!player) {
			throw new ForbiddenException(
				'You are not a member of this lobby',
			);
		}

		if (lobby.ownerId === userId) {
			await this.prisma.lobby.delete({
				where: {
					id: lobbyId,
				},
			});

			return {
				deleted: true,
			};
		}

		await this.prisma.lobbyPlayer.delete({
			where: {
				id: player.id,
			},
		});

		return {
			deleted: false,
		};
	}

	async leaveCurrentLobby(
	userId: number,
	)
	{
		const player = await this.prisma.lobbyPlayer.findFirst({
			where: {
				userId,
			},
			include: {
				lobby: true,
			},
		});

		if (!player) {
			return {
				left: false,
				deleted: false,
				lobbyId: null,
			};
		}

		if (player.lobby.ownerId === userId) {
			await this.prisma.lobby.delete({
				where: {
					id: player.lobbyId,
				},
			});

			return {
				left: true,
				deleted: true,
				lobbyId: player.lobbyId,
			};
		}

		await this.prisma.lobbyPlayer.delete({
			where: {
				id: player.id,
			},
		});

		return {
			left: true,
			deleted: false,
			lobbyId: player.lobbyId,
		};
	}

	async setReady(
		userId: number,
		lobbyId: string,
		ready: boolean,
	)
	{
		const lobby = await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		if (lobby.status !== 'WAITING') {
			throw new ConflictException(
				'Lobby is not waiting for players',
			);
		}

		const player = lobby.players.find(
			(player) => player.userId === userId,
		);

		if (!player) {
			throw new ForbiddenException(
				'You are not a member of this lobby',
			);
		}

		await this.prisma.lobbyPlayer.update({
			where: {
				id: player.id,
			},
			data: {
				ready,
			},
		});

		return this.getLobby(userId, lobbyId);
	}

	async setColor(
		userId: number,
		lobbyId: string,
		color: string,
	)
	{
		const lobby = await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		if (lobby.status !== 'WAITING') {
			throw new ConflictException(
				'Lobby is not waiting for players',
			);
		}

		const player = lobby.players.find(
			(player) => player.userId === userId,
		);

		if (!player) {
			throw new ForbiddenException(
				'You are not a member of this lobby',
			);
		}

		const takenByOther = lobby.players.some(
			(other) => other.userId !== userId && other.color === color,
		);

		if (takenByOther) {
			throw new ConflictException(
				'Color already taken in this lobby',
			);
		}

		await this.prisma.lobbyPlayer.update({
			where: {
				id: player.id,
			},
			data: {
				color,
			},
		});

		return this.getLobby(userId, lobbyId);
	}

	async startGame(
		userId: number,
		lobbyId: string,
	)
	{
		const lobby = await this.prisma.lobby.findUnique({
			where: {
				id: lobbyId,
			},
			include: {
				players: true,
			},
		});

		if (!lobby) {
			throw new NotFoundException('Lobby not found');
		}

		const isMember = lobby.players.some(
			(player) => player.userId === userId,
		);

		if (!isMember) {
			throw new ForbiddenException(
				'You are not a member of this lobby',
			);
		}

		if (lobby.ownerId !== userId) {
			throw new ForbiddenException(
				'Only the lobby owner can start the game',
			);
		}

		if (lobby.status !== 'WAITING') {
			throw new ConflictException(
				'Game has already started',
			);
		}

		if (lobby.players.length < 2) {
			throw new ConflictException(
				'At least 2 players are required to start the game',
			);
		}

		const gameId = randomUUID()

		const colorByUserId = this.resolvePlayerColors(
			lobby.players.map((p) => ({ userId: p.userId, color: p.color })),
		);

		this.gameManagerService.createGame(
			gameId,
			lobbyId,
			lobby.players.map((p) => ({
				id: p.userId,
				username: p.username,
				color: colorByUserId.get(p.userId)! as PlayerColor,
			})),
		);

		const updateLobby = await this.prisma.lobby.update({
			where: { id: lobbyId },
			data: { status: 'IN_GAME' },
			include: { players: true }
		})

		return {
			...updateLobby,
			gameId	
		};
	}

	private async ensureUserIsNotInLobby(
		userId: number,
	)
	{
		const existingPlayer =
			await this.prisma.lobbyPlayer.findFirst({
				where: {
					userId,
				},
			});

		if (existingPlayer) {
			throw new ConflictException(
				'User is already in a lobby',
			);
		}
	}

	private async generateUniqueCode()
	{
		const characters =
			'ABCDEFGHJKLMNPQRSTUVWXYZ23456789';

		for (let attempt = 0; attempt < 10; attempt++) {
			let code = '';

			for (let i = 0; i < 6; i++) {
				const index = Math.floor(
					Math.random() * characters.length,
				);

				code += characters[index];
			}

			const existingLobby =
				await this.prisma.lobby.findUnique({
					where: {
						code,
					},
				});

			if (!existingLobby) {
				return code;
			}
		}

		throw new ConflictException(
			'Unable to generate a unique lobby code',
		);
	}

	private resolvePlayerColors(
		players: { userId: number; color: string | null }[],
	): Map<number, string>
	{
		const taken = new Set(
			players
				.map((p) => p.color)
				.filter((c): c is string => c !== null),
		);

		const available = AVAILABLE_COLORS.filter((c) => !taken.has(c));
		const result = new Map<number, string>();
		let fallbackIndex = 0;

		players.forEach((p) => {
			if (p.color && (AVAILABLE_COLORS as readonly string[]).includes(p.color)) {
				result.set(p.userId, p.color);
			} else {
				result.set(p.userId, available[fallbackIndex++]);
			}
		});

		return result;
	}
}
