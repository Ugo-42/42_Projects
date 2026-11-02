import { Injectable } from '@nestjs/common';

@Injectable()
export class LobbyService {
	private readonly gameServiceUrl =
		process.env.GAME_SERVICE_URL ||
		`http://${process.env.GAME_SERVICE_HOST || 'localhost'}:${process.env.GAME_SERVICE_PORT || '3002'}`;

	async isLobbyMember(
		lobbyId: string,
		token: string,
	): Promise<boolean> {
		const controller = new AbortController();
		const timeout = setTimeout(() => controller.abort(), 2000);

		try {
			const response = await fetch(
				`${this.gameServiceUrl}/lobbies/${lobbyId}`,
				{
					headers: {
						Authorization: `Bearer ${token}`,
					},
					signal: controller.signal,
				},
			);

			return response.ok;
		} catch {
			return false;
		} finally {
			clearTimeout(timeout);
		}
	}
}