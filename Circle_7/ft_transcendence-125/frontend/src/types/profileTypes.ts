export type Achievement = {
	type: "PLAY_GAME" | "WIN_GAME" | "PLACE_10_BOMBS"
	rewardXp: number
	unlockedAt: string
}

export type ProfilePrivate = {
	id: number
	username: string
	email: string
	avatarUrl: string | null
	bio: string | null
	level: number
	xp: number
	wins: number
	losses: number
	bombplaced: number
	enemyKill: number
	twoFactorEnabled: boolean
	createdAt: string
	achievements: Achievement[]
}

export type Profile = {
	id: number
	username: string
	avatarUrl: string | null
	bio: string | null
	level: number
	xp: number
	wins: number
	losses: number
	bombplaced: number
	enemyKill: number
	createdAt: string
	achievements: Achievement[]
}

export type ProfileEditRequest = {
	username?: string
	email?: string
	bio?: string
	avatarUrl?: string
	currentPassword?: string
	newPassword?: string
}