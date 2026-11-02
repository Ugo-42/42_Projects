export type Friend = {
	id: number
	username: string
	avatarUrl?: string | null
}

export type FriendRequest = {
	id: number
	sender: {
		id: number
		username: string
		avatarUrl?: string | null
	}
}

export type UserSearchResult = {
	id: number
	username: string
	avatarUrl: string | null
}
