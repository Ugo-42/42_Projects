import Card from "../ui/Card"
import Button from "../ui/Button"
import Avatar from "../ui/Avatar"
import Badge from "../ui/Badge"
import Input from "../ui/Input"

import ProfileRow from "../layouts/ProfileRow"

import { getUser } from "@/utils/storage"
import { deleteAccount, getMyProfile } from "@/services/profileService"
import { disableTwoFactor, enableTwoFactor } from "@/services/authService"
import { useEffect, useState } from "react"
import { useTranslation } from "react-i18next"
import { validateProfileEdit } from "@/utils/validation"
import { updateAccount, uploadAvatar } from "@/services/profileService"
import type { ProfilePrivate } from "@/types/profileTypes"
import Spinner from "../ui/Spinner"

type ProfileCardProps = {
	isOpen: boolean
	onClose: () => void
}

function ProfileCard({ isOpen, onClose }: ProfileCardProps) {
	
	const { t } = useTranslation()

	const [user, setUser] = useState<ProfilePrivate | null>(null)
	const [loading, setLoading] = useState(true)

	const [mode, setMode] = useState<"view" | "edit">("view")
	const [activeTab, setActiveTab] = useState<"stats" | "achievements">("stats")

	const [username, setUsername] = useState('')
	const [email, setEmail] = useState('')
	const [currentPassword, setCurrentPassword] = useState('')
    const [newPassword, setNewPassword] = useState('')
	const [confirmPassword, setConfirmPassword] = useState('')
	const [avatarFile, setAvatarFile] = useState<File | null>(null)
	const [error, setError] = useState('')
	const [showDeleteConfirm, setShowDeleteConfirm] = useState(false)
	const [twoFactorLoading, setTwoFactorLoading] = useState(false)

	const handleDeleteAccount = async () => {
		try {
			await deleteAccount()
			window.location.href = "/"
		} catch (error) {
			console.error("Error deleting account:", error)
			setError(t("profile.delete_failed"))
		}
	}

	const handleTwoFactorToggle = async () => {
		if (!user) return

		setTwoFactorLoading(true)
		setError('')
		try {
			const response = user.twoFactorEnabled
				? await disableTwoFactor()
				: await enableTwoFactor()
			setUser((currentUser) => currentUser
				? { ...currentUser, twoFactorEnabled: response.twoFactorEnabled }
				: currentUser)
		} catch {
			setError(t('2FA.two_factor_update_failed'))
		} finally {
			setTwoFactorLoading(false)
		}
	}

	useEffect(() => {
		async function fetchProfile() {
			const cachedUser = getUser()
			if (!cachedUser) {
				setLoading(false)
				return
			}
			try {
				const response = await getMyProfile()
				setUser(response)
			} catch (error) {
				console.error("Error fetching profile:", error)
			} finally {
				setLoading(false)
			}
		}
		fetchProfile()
	}, [])

	if (!isOpen)
		return null

	if (!user) {
		return (
			<p>No user connected.</p>
		)
	}

	if (loading) {
		return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Spinner size="sm" variant="light" />
		</div>
		)
	}

	const handleSaveChanges = async (e: React.FormEvent<HTMLFormElement>) => {

		e.preventDefault()
		setError('')

		const validationError = validateProfileEdit(
			{
				username,
				email,
				currentPassword,
				newPassword,
			},
			confirmPassword,
		)
		if (validationError) {
			setError(validationError)
			return
		}

		const hasChanges =
			(username !== "" &&
				username !== user?.username) ||
			(email !== "" &&
				email !== user?.email) ||
			Boolean(newPassword) ||
			Boolean(avatarFile)

		if (!hasChanges) {
			setError("No changes to save.")
			return
		}

		try {
			const accountChanged =
				(username !== "" && username !== user.username) ||
				(email !== "" && email !== user.email) ||
				Boolean(newPassword)
			if (accountChanged) {
				await updateAccount({
					username: username && username !== user.username ? username : undefined,
					email: email && email !== user.email ? email : undefined,
					currentPassword: newPassword ? currentPassword || undefined : undefined,
					newPassword: newPassword || undefined,
				})
			}
			if (avatarFile) {
				await uploadAvatar(avatarFile)
			}
			setUsername('')
			setEmail('')
			setCurrentPassword('')
			setNewPassword('')
			setConfirmPassword('')
			setAvatarFile(null)

			setMode("view")
		} catch (error){
			if (error instanceof Error) {
				setError(t("profile.update_failed"))
			}
			else {
				setError(t("profile.update_failed"))
			}
		}
	}

	return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Card
				titleKey=""
				isOpen={isOpen}
				onClose={onClose}
			>
			<div className="flex flex-col items-center gap-3 max-h-[80vh] scrollbar-thin scrollbar-thumb-info scrollbar-track-transparent overflow-y-auto">
				<div className="relative inline-block">
					<Avatar pseudo={user.username} size="lg" src={user.avatarUrl ?? undefined} />
					<Badge labelKey="status.online" variant="success" className="absolute top-1 -right-1" />
				</div>

				<div className="text-center">
					<h3 className="text-3xl font-micro-5 text-info">
						{user.username}
					</h3>

					<p className="text-white/60">
						{user.email}
					</p>
				</div>

				{mode === "view" && (
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
								<ProfileRow label={t("user_info.xp")} value={user.xp} />
								<ProfileRow label={t("user_info.wins")} value={user.wins} />
								<ProfileRow label={t("user_info.losses")} value={user.losses} />
							</div>
						)}

						{activeTab === "achievements" && (
							<div className="flex flex-col items-center gap-3 mt-5 py-5 px-5">
								{user.achievements.length === 0 ? (
									<Badge labelKey="achievements.none" variant="error" />
								) : user.achievements.map((achievement) => (
									<div key={achievement.type} className="flex items-center gap-2">
										<Badge labelKey={`achievements.${achievement.type}`} variant="success" />
										<span className="text-info text-sm">+{achievement.rewardXp} XP</span>
									</div>
								))}
							</div>

						)}
					</div>
					<footer className="flex justify-center w-full mt-10">
						<Button
							variant="primary"
							onClick={() => setMode("edit")}
						>
							{t("button.edit")}
						</Button>
					</footer>
				</div>
				)}

				{mode === "edit" && (
				<form onSubmit={handleSaveChanges}>
					<div>
						<div className="md:flex md:flex-col md:gap-2">
							{error && (
								<div className="text-error text-center text-sm">
									{error}
								</div>
							)}							
							<label className="inline-block cursor-pointer bg-info/80 hover:bg-info text-white font-micro-5 text-lg px-4 py-2 rounded-lg text-center">
								{t("button.change_avatar")}
								<input
									type="file"
									accept="image/jpeg,image/png,image/webp,image/gif"
									className="hidden"
									onChange={(e) => setAvatarFile(e.target.files?.[0] ?? null)}
								/>
							</label>
							<div className="flex flex-col items-center gap-2 mt-2">
								<Button
									variant={user.twoFactorEnabled ? "error" : "success"}
									onClick={handleTwoFactorToggle}
									disabled={twoFactorLoading}
								>
									{twoFactorLoading ? <Spinner size="sm" variant="light" /> : t(user.twoFactorEnabled ? "2FA.disable_two_factor" : "2FA.enable_two_factor")}
								</Button>
							</div>
							<Input labelKey="profile.change_username" placeHolderKey="profile.new_username" type="text" value={username} onChange={(e) => setUsername(e.target.value)} />
							<Input labelKey="profile.change_email" placeHolderKey="profile.new_email" type="email" value={email} onChange={(e) => setEmail(e.target.value)} />
							<Input labelKey="profile.current_password" placeHolderKey="profile.current_password" type="password" value={currentPassword} onChange={(e) => setCurrentPassword(e.target.value)} />
							<Input labelKey="profile.change_password" placeHolderKey="profile.new_password" type="password" value={newPassword} onChange={(e) => setNewPassword(e.target.value)} />
							<Input labelKey="profile.confirm_new_password" placeHolderKey="profile.confirm_new_password" type="password" value={confirmPassword} onChange={(e) => setConfirmPassword(e.target.value)} />
							<div className="flex justify-center w-full mt-5">
								<Button variant="error" onClick={() => setShowDeleteConfirm(true)}>
									{t("button.delete_account")}
								</Button>
							</div>
						</div>

						<footer className="flex justify-center w-full mt-10 gap-2">
							<Button
								variant="error"
								onClick={() => setMode("view")}
							>
								{t("button.cancel")}
							</Button>
							<Button
								variant="success"
								type="submit"
							>
								{t("button.confirm")}
							</Button>
						</footer>
					</div>
				</form>
				)}
			</div>
			</Card>

			{showDeleteConfirm && (
				<div className="fixed inset-0 flex items-center justify-center z-50">
					<Card titleKey="button.delete_account" isOpen={true} onClose={() => setShowDeleteConfirm(false)}>
						<p className="text-center text-white/80">{t("questions.really_sure")}</p>
						<div className="flex justify-center gap-2 mt-4">
							<Button variant="warning" onClick={() => setShowDeleteConfirm(false)}>
								{t("button.cancel")}
							</Button>
							<Button variant="error" onClick={handleDeleteAccount}>
								{t("button.delete")}
							</Button>
						</div>
					</Card>
				</div>
			)}
		</div>
	)
}

export default ProfileCard