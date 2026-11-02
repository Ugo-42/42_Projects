import Avatar from "../ui/Avatar"
import Card from "../ui/Card"
import Spinner from "../ui/Spinner"

import { useState, useEffect } from "react"
import { getLeaderboard } from "@/services/leaderboardService"
import type { LeaderboardEntry } from "@/types/leaderboardTypes"

type LeaderboardCardProps = {
	isOpen: boolean
	onClose: () => void
}

function LeaderboardCard({ isOpen, onClose }: LeaderboardCardProps) {
	const [rankings, setRankings] = useState<LeaderboardEntry[]>([])
	const [loading, setLoading] = useState(true)

	useEffect(() => {
		async function fetchLeaderboard() {
			try {
				const response = await getLeaderboard()
				const sorted = [...response].sort((a, b) => b.value - a.value)
				setRankings(sorted.map((entry, index) => ({ ...entry, rank: index + 1 })))
			} catch (error) {
				console.error("Error fetching leaderboard:", error)
			} finally {
				setLoading(false)
			}
		}
		fetchLeaderboard()
	}, [])

	if (!isOpen)
		return null

	if (loading) {
		return (
			<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
				<Spinner size="sm" variant="light" />
			</div>
		)
	}

	return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Card
				titleKey="nav.leaderboard"
				isOpen={isOpen}
				onClose={onClose}
			>
			<ul className="max-h-64 scrollbar-thin scrollbar-thumb-info scrollbar-track-transparent overflow-y-auto">
				{rankings.map((entry) => (
					<li key={entry.userId} className="flex items-center justify-between p-2 rounded-lg">
						<div className="flex items-center gap-3">
							<span className="w-6 text-center text-info text-lg font-micro-5">{entry.rank}</span>
							<Avatar pseudo={entry.username} size="sm" src={entry.avatarUrl ?? undefined} />
							<div>
								<p className="font-micro-5 text-info">{entry.username}</p>
								{entry.byline && <p className="text-xs text-white/50">{entry.byline}</p>}
							</div>
						</div>
						<span className="font-micro-5 text-lg text-info">{entry.value.toLocaleString()} XP</span>
					</li>
				))}
			</ul>
			</Card>
		</div>
	)
}

export default LeaderboardCard