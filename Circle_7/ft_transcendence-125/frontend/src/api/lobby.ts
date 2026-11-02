import type { Lobby } from "@/types/lobby"
 
import { apiFetch } from "./fetch"
 
 
type CreateLobbyRequest = {
	name: string
	isPrivate: boolean
}
 
 
async function lobbyRequest<T>(
	url: string,
	options: RequestInit = {},
): Promise<T> {
 
	const response = await apiFetch(url, {
		...options,
 
		headers: {
			"Content-Type": "application/json",
			...options.headers,
		},
	})
 
 
	if (!response.ok) {
 
		let message = "Lobby request failed"
 
		try {
			const error = await response.json()
 
			message =
				error.message ||
				error.error ||
				message
 
		} catch {}
 
		throw new Error(message)
	}
 
 
	return response.json()
}
 
 
 
export async function getPublicLobbies(): Promise<Lobby[]> {
 
	return lobbyRequest<Lobby[]>(
		"/api/game/lobbies",
		{
			method: "GET",
		},
	)
}
 
export async function getLobby(
	lobbyId: string,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		`/api/game/lobbies/${lobbyId}`,
		{
			method: "GET",
		},
	)
}
 
 
export async function createLobby(
	data: CreateLobbyRequest,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		"/api/game/lobbies",
		{
			method: "POST",
 
			body: JSON.stringify({
				name: data.name,
				isPrivate: data.isPrivate,
			}),
		},
	)
}
 
export async function joinPublicLobby(
	lobbyId: string,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		`/api/game/lobbies/${lobbyId}/join`,
		{
			method: "POST",
		},
	)
}
 
 
export async function joinLobbyByCode(
	code: string,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		"/api/game/lobbies/join-by-code",
		{
			method: "POST",
 
			body: JSON.stringify({
				code: code.trim().toUpperCase(),
			}),
		},
	)
}
 
 
 
export async function leaveLobby(lobbyId: string,): 
Promise<{
    deleted: boolean}> 
{
    return lobbyRequest<{deleted: boolean}>
	(
        `/api/game/lobbies/${lobbyId}/leave`,
        {
            method: "POST",
        },
    )
}
 
 
export async function setLobbyReady(
	lobbyId: string,
	ready: boolean,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		`/api/game/lobbies/${lobbyId}/ready`,
		{
			method: "PATCH",
 
			body: JSON.stringify({
				ready,
			}),
		},
	)
}
 
 
export async function setLobbyColor(
	lobbyId: string,
	color: string,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		`/api/game/lobbies/${lobbyId}/color`,
		{
			method: "PATCH",
 
			body: JSON.stringify({
				color,
			}),
		},
	)
}
 
 
export async function startLobbyGame(
	lobbyId: string,
): Promise<Lobby> {
 
	return lobbyRequest<Lobby>(
		`/api/game/lobbies/${lobbyId}/start`,
		{
			method: "POST",
		},
	)
}
 
 
export async function leaveCurrentLobby(): Promise<{
	left: boolean
	deleted: boolean
}> {
 
	return lobbyRequest<{
		left: boolean
		deleted: boolean
	}>(
		"/api/game/lobbies/leave-current",
		{
			method: "POST",
		},
	)
}
