import { Injectable } from '@nestjs/common';

@Injectable()
export class FriendshipService {
	private readonly userServiceUrl =
		process.env.USER_SERVICE_URL ||
		`http://${process.env.USER_SERVICE_HOST || 'localhost'}:${process.env.USER_SERVICE_PORT || '3001'}`;

	async areFriends(
		friendId: number,
		token: string,
	): Promise<boolean> {
		const controller = new AbortController();
		const timeout = setTimeout(() => controller.abort(), 2000);

		try {
			const response = await fetch(
				`${this.userServiceUrl}/friends/${friendId}/status`,
				{
					headers: {
						Authorization: `Bearer ${token}`,
					},
					signal: controller.signal,
				},
			);

			if (!response.ok) {
				return false;
			}

			const result = await response.json() as {
				areFriends?: boolean;
			};
			return result.areFriends === true;
		} catch {
			return false;
		} finally {
			clearTimeout(timeout);
		}
	}
}