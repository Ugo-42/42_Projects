import Card from "../ui/Card"
import Button from "../ui/Button"
import Avatar from "../ui/Avatar"
import Badge from "../ui/Badge"
import Spinner from "../ui/Spinner"
import Toast from "../ui/Toast"

import ProfileRow from "../layouts/ProfileRow"

import type { Profile } from "@/types/profileTypes"
import { useTranslation } from "react-i18next"
import { useState } from "react"
import { useEffect } from "react"
import { getProfileById } from "@/services/profileService"
import { usePresence } from "@/hooks/usePresence"

type ProfileFriendsCardProps = {
	userId: number
	isOpen: boolean
	onClose: () => void
}

function ProfileFriendsCard({ userId, isOpen, onClose }: ProfileFriendsCardProps) {

	const { t } = useTranslation()
	const {isOnline, fetchPresence} = usePresence()

	const [friend, setFriend] = useState<Profile | null>(null)
	const [loading, setLoading] = useState(true)
	const [activeTab, setActiveTab] = useState<"stats" | "achievements">("stats")

	useEffect(() => {
		async function fetchFriend() {
			try {
				const response = await getProfileById(userId)
				setFriend(response)
			}
			catch (error) {
				console.error("Error fetching friend:", error)
			}
			finally {
				setLoading(false)
			}
		}

		fetchFriend()
	}, [userId])

	useEffect(() => {
		fetchPresence([userId])
	}, [userId, fetchPresence])

	if (!isOpen)
		return null

	if (loading) {
		return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Spinner size="sm" variant="light" />
		</div>
		)
	}

	if (!friend) {
		return (
		<div className="fixed inset-0 flex items-center justify-center z-40">
			<Toast labelKey="toast.friends.not_found" variant="error" onClose={onClose}>
			</Toast>
		</div>
		)
	}

	return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Card
				titleKey="nav.friends"
				isOpen={isOpen}
				onClose={onClose}
				footer={
					<Button
						variant="primary"
						onClick={onClose}
					>
						{t("button.close")}
					</Button>
				}
			>

			<div className="flex flex-col items-center gap-3">
				<div className="relative inline-block">
					<Avatar pseudo={friend.username} size="lg" src={friend.avatarUrl ?? undefined} />
					<Badge
						labelKey={isOnline(userId) ? "status.online" : "status.offline"}
						variant={isOnline(userId) ? "success" : "error"}
						className="absolute top-1 -right-1"
					/>
				</div>

				<div className="text-center">
					<h3 className="text-3xl font-micro-5 text-info">
						{friend.username}
					</h3>

					{friend.bio && (
						<p className="text-white/60">
							{friend.bio}
						</p>
					)}
				</div>

				<div>
					<div className="flex flex-col items-center gap-2 py-2 px-10">
						<Button
							variant={activeTab === "stats" ? "secondary" : "primary"}
							onClick={() => setActiveTab("stats")}>
								{t("button.stats")}
						</Button>
						<Button
							variant={activeTab === "achievements" ? "secondary" : "primary"}
							onClick={() => setActiveTab("achievements")}>
							{t("button.achievements")}
						</Button>
					</div>

					<div className="w-full mt-5 space-y-5">
						{activeTab === "stats" && (
							<div>
								<ProfileRow label={t("user_info.xp")} value={friend.xp} />
								<ProfileRow label={t("user_info.wins")} value={friend.wins} />
								<ProfileRow label={t("user_info.losses")} value={friend.losses} />
							</div>
						)}

						{activeTab === "achievements" && (
							<div className="flex flex-col items-center gap-3 mt-5 py-5 px-5">
								{friend.achievements.length === 0 ? (
									<Badge labelKey="achievements.none" variant="error" />
								) : friend.achievements.map((achievement) => (
									<div key={achievement.type} className="flex items-center gap-2">
										<Badge labelKey={`achievements.${achievement.type}`} variant="success" />
										<span className="text-info text-sm">+{achievement.rewardXp} XP</span>
									</div>
								))}
							</div>

						)}
					</div>
				</div>
			</div>
			</Card>
		</div>
	)
}

export default ProfileFriendsCard