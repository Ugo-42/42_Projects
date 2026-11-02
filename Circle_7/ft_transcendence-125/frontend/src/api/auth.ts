import type {
	AuthResponse,
	LoginRequest,
	LoginResponse,
	RegisterRequest,
	TwoFactorSetupResponse,
	TwoFactorStatusResponse,
} from "../types/authTypes"
 
import type { User } from "@/types/authTypes"
 
import { apiFetch } from "./fetch"
 
const AUTH_URL = "/api/auth"
 
 
export async function getMe(): Promise<User> {
 
	const response = await apiFetch(`${AUTH_URL}/me`, {
		method: "GET",
	})
 
	if (!response.ok) {
		throw new Error("Invalid session")
	}
 
	const data: { user: User } = await response.json()
 
	return data.user
}
 
 
export async function login(data: LoginRequest) {
	const response = await fetch("/api/auth/login", {
		method: "POST",
		headers: {
			"Content-Type": "application/json",
		},
		body: JSON.stringify(data),
	})
 
	if (!response.ok) {
		let message = "Login failed"
		try {
			const errorData: { message?: string | string[] } = await response.json()
			if (Array.isArray(errorData.message)) {
				message = errorData.message.join(" ")
			} else if (errorData.message) {
				message = errorData.message
			}
		} catch {
		}
		throw new Error(message)
	}
 
	return response.json() as Promise<LoginResponse>
}
 
 
export async function register(data: RegisterRequest) {
	const response = await fetch("/api/auth/register", {
		method: "POST",
		headers: {
			"Content-Type": "application/json",
		},
		body: JSON.stringify(data),
	})
 
	if (!response.ok) {
		throw new Error("Registration failed")
	}
 
	return response.json() as Promise<AuthResponse>
}
 
export async function refreshAccessToken(refreshToken: string): Promise<{ accessToken: string }> {
	const response = await fetch(`${AUTH_URL}/refresh`, {
		method: "POST",
		headers: {
			"Content-Type": "application/json",
		},
		body: JSON.stringify({ refreshToken }),
	})
 
	if (!response.ok) {
		throw new Error("Refresh failed")
	}
 
	return response.json()
}
 
async function postAuthenticated<T>(path: string, body: unknown): Promise<T> {
	const response = await apiFetch(`${AUTH_URL}${path}`, {
		method: "POST",
		headers: {
			"Content-Type": "application/json",
		},
		body: JSON.stringify(body),
	})
 
	if (!response.ok) {
		throw new Error("2FA request failed")
	}
 
	return response.json() as Promise<T>
}
 
export function generateTwoFactor(appName?: string) {
	return postAuthenticated<TwoFactorSetupResponse>("/2fa/generate", {
		...(appName ? { appName } : {}),
	})
}
 
export function enableTwoFactor() {
	return postAuthenticated<TwoFactorStatusResponse>("/2fa/enable", {})
}
 
export function disableTwoFactor() {
	return postAuthenticated<TwoFactorStatusResponse>("/2fa/disable", {})
}
 
export async function verifyTwoFactor(twoFactorToken: string, code: string) {
	const response = await fetch(`${AUTH_URL}/2fa/verify`, {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		body: JSON.stringify({ twoFactorToken, code }),
	})
 
	if (!response.ok) {
		throw new Error("2FA verification failed")
	}
 
	return response.json() as Promise<AuthResponse>
}