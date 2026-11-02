export type LobbyStatus =
    | "WAITING"
    | "IN_GAME"

export type LobbyPlayer = {
    id: number
    userId: number
    username: string
	color: string | null
    ready: boolean
    joinedAt: string
}

export type Lobby = {
    id: string
    name: string
    ownerId: number
    isPrivate: boolean
    code: string | null
    status: LobbyStatus
    maxPlayers: number
    createdAt: string
    players: LobbyPlayer[]
}
