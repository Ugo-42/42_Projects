export type User = {
	id: number
	username: string
	email: string
	level: number
	wins: number
	losses: number
	avatarUrl?: string | null
	twoFactorEnabled?: boolean
}

export type LoginRequest = {
	identifier: string
	password: string
}

export type RegisterRequest = {
	username: string
	email: string
	password: string
}

export type AuthResponse = {
	accessToken: string
	refreshToken: string
	user: User
}

export type TwoFactorPendingResponse = {
	status: "2fa_required"
	twoFactorRequired: true
	twoFactorToken: string
	user: Pick<User, "id" | "email" | "username">
}

export type LoginResponse = AuthResponse | TwoFactorPendingResponse

export type TwoFactorSetupResponse = {
	twoFactorEnabled: boolean
	qrCodeBase64: string
	otpauthUrl: string
	manualEntryKey: string
}

export type TwoFactorStatusResponse = {
	twoFactorEnabled: boolean
	message: string
}