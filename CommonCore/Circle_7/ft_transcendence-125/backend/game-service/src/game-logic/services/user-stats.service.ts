import { Injectable, Logger } from '@nestjs/common'

@Injectable()
export class UserStatsService {
	private readonly logger = new Logger(UserStatsService.name)

	async recordGameResult(
		userId: number,
		result: 'win' | 'loss' | 'draw',
		bombplaced: number,
		enemyKill: number,
		xp: number,
	): Promise<void> {
		const host = process.env.USER_SERVICE_HOST || 'localhost'
		const port = process.env.USER_SERVICE_PORT || '3001'
		const baseUrl = process.env.USER_SERVICE_URL || `http://${host}:${port}`
		const serviceKey = process.env.GAME_SERVICE_INTERNAL_KEY

		if (!serviceKey) {
			this.logger.error('GAME_SERVICE_INTERNAL_KEY is not configured')
			return
		}

		try {
			const response = await fetch(`${baseUrl}/internal/users/game-result`, {
				method: 'POST',
				headers: {
					'content-type': 'application/json',
					'x-internal-service-key': serviceKey,
				},
				body: JSON.stringify({
					userId,
					result,
					bombplaced,
					enemyKill,
					xp,
				}),
			})

			if (!response.ok) {
				throw new Error(`user-service returned HTTP ${response.status}`)
			}
		} catch (error) {
			this.logger.error(
				`Could not record result for user ${userId}`,
				error instanceof Error ? error.stack : String(error),
			)
		}
	}
}