import Modal from "../ui/Modal"
import Button from "../ui/Button"

import { useNavigate } from "react-router-dom"
import { useTranslation } from "react-i18next"
import { leaveCurrentLobby } from "@/services/lobbyService"
import { useAuth } from "@/hooks/useAuth"

type LogoutModalProps = {
	isOpen: boolean
	onClose: () => void
}

function LogoutModal({ isOpen, onClose }: LogoutModalProps) {

	const { t } = useTranslation()
	const navigate = useNavigate()
	const { logoutLocal } = useAuth()

	const handleLogout = async () => {
		try {
			await leaveCurrentLobby()
		} catch (error) {
			console.error(
				"[LOGOUT] Failed to leave lobby:",
				error,
			)
		}
		logoutLocal()
		navigate("/")
	}

	return (
		<Modal
			isOpen={isOpen}
			onClose={onClose}
			footer={
				<div className="flex gap-4">
					<Button
						variant="secondary"
						onClick={onClose}
					>
						{t("button.cancel")}
					</Button>

					<Button
						variant="error"
						onClick={handleLogout}
					>
						{t("nav.logout")}
					</Button>
				</div>
			}
		>
			<div className="flex flex-col items-center gap-6 p-6">

				<h2 className="text-4xl font-micro-5 text-info">
					{t("nav.logout")}
				</h2>

				<p className="text-center text-lg">
					{t("questions.really_sure")}
				</p>

			</div>
		</Modal>
	)
}

export default LogoutModal