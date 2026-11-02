import * as leaderboardApi from "@/api/leaderboard"

export async function getLeaderboard() {
	return leaderboardApi.getLeaderboard()
}