import * as lobbyApi from "@/api/lobby"

export const getPublicLobbies =
	lobbyApi.getPublicLobbies

export const getLobby =
	lobbyApi.getLobby

export const createLobby =
	lobbyApi.createLobby

export const joinPublicLobby =
	lobbyApi.joinPublicLobby

export const joinLobbyByCode =
	lobbyApi.joinLobbyByCode

export const leaveLobby =
	lobbyApi.leaveLobby

export const setLobbyReady =
	lobbyApi.setLobbyReady

export const startLobbyGame =
	lobbyApi.startLobbyGame

export const leaveCurrentLobby =
	lobbyApi.leaveCurrentLobby

export { setLobbyColor } from "@/api/lobby";
