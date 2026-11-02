import * as authApi from "../api/auth"
import { connectSocket, disconnectSockets } from "./socketService"
import type { AuthResponse, LoginRequest, LoginResponse, RegisterRequest } from "../types/authTypes"
import { leaveCurrentLobby } from "./lobbyService"

export async function login(data: LoginRequest) {
	const response = await authApi.login(data)

	if (isAuthenticatedResponse(response)) {
		storeSession(response)
		try { await leaveCurrentLobby() }
		catch (error) {
			console.error("[LOGIN] Failed to cleanup stale lobby:", error)
		}
		sessionStorage.removeItem("currentLobbyId")
		sessionStorage.removeItem("currentLobbyName")
		sessionStorage.removeItem("currentGameId")
		sessionStorage.removeItem("inGame")
		connectSocket()
	}

	return response
}

export async function register(data: RegisterRequest) {
	const response = await authApi.register(data)

	if (isAuthenticatedResponse(response)) {
		storeSession(response)
		connectSocket()
	}

	return response
}

export async function verifyTwoFactor(twoFactorToken: string, code: string) {
	const response = await authApi.verifyTwoFactor(twoFactorToken, code)
	storeSession(response)
	connectSocket()
	return response
}

export const generateTwoFactor = authApi.generateTwoFactor
export const enableTwoFactor = authApi.enableTwoFactor
export const disableTwoFactor = authApi.disableTwoFactor

function isAuthenticatedResponse(response: LoginResponse | AuthResponse): response is AuthResponse {
	return "accessToken" in response && "refreshToken" in response
}

function storeSession(response: AuthResponse) {
	localStorage.setItem("user", JSON.stringify(response.user))
	localStorage.setItem("token", response.accessToken)
	localStorage.setItem("refreshToken", response.refreshToken)
}

export async function getCurrentUser() {
	const user = await authApi.getMe()
	localStorage.setItem("user", JSON.stringify(user))
	return user
}

export function clearSession() {
	disconnectSockets()
	localStorage.removeItem("token")
	localStorage.removeItem("refreshToken")
	localStorage.removeItem("user")
	sessionStorage.removeItem("currentLobbyId")
	sessionStorage.removeItem("currentLobbyName")
	sessionStorage.removeItem("currentGameId")
	sessionStorage.removeItem("inGame")
}

export function getStoredUser() {
	const storedUser = localStorage.getItem("user")
	if (!storedUser) return null

	try {
		return JSON.parse(storedUser)
	} catch {
		return null
	}
}