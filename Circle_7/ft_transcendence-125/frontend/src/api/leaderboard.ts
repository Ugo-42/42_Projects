import type { LeaderboardEntry } from "@/types/leaderboardTypes"
 
import { apiFetch } from "./fetch"
 
const LEADERBOARD_URL = "/api/user/users/leaderboard"
 
export async function getLeaderboard(): Promise<LeaderboardEntry[]> {
 
	const response = await apiFetch(
		LEADERBOARD_URL,
		{
			method: "GET",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to fetch leaderboard")
 
	return response.json()
}