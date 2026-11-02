import { refreshAccessToken } from "./auth"
 
let refreshPromise: Promise<string | null> | null = null
 
async function getNewAccessToken(): Promise<string | null> {
	if (!refreshPromise) {
		refreshPromise = (async () => {
			const refreshToken = localStorage.getItem("refreshToken")
			if (!refreshToken) return null
 
			try {
				const response = await refreshAccessToken(refreshToken)
				localStorage.setItem("token", response.accessToken)
				return response.accessToken
			} catch {
				return null
			} finally {
				refreshPromise = null
			}
		})()
	}
	return refreshPromise
}
 
export async function apiFetch(url: string, options: RequestInit = {}): Promise<Response> {
	const token = localStorage.getItem("token")
 
	const response = await fetch(url, {
		...options,
		headers: {
			...options.headers,
			...(token ? { Authorization: `Bearer ${token}` } : {}),
		},
	})
 
	if (response.status !== 401) {
		return response
	}
 
	const newToken = await getNewAccessToken()
 
	if (!newToken) {
		localStorage.removeItem("user")
		localStorage.removeItem("token")
		localStorage.removeItem("refreshToken")
		window.location.href = "/"
		throw new Error("Session expired")
	}
 
	return fetch(url, {
		...options,
		headers: {
			...options.headers,
			Authorization: `Bearer ${newToken}`,
		},
	})
}