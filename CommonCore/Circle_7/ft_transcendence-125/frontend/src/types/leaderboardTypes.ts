export type LeaderboardEntry = {
	userId: number
	username: string
	avatarUrl: string | null
	value: number
	byline?: string
	rank: number
}