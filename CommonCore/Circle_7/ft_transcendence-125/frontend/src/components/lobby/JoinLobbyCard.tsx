import { useState } from "react"
import { useTranslation } from "react-i18next"

import Button from "@/components/ui/Button"
import Input from "@/components/ui/Input"
import Card from "@/components/ui/Card"

type JoinLobbyCardProps = {
	isOpen: boolean
	onClose: () => void
	onJoin: (code: string) => void
}

function JoinLobbyCard({
	isOpen,
	onClose,
	onJoin,
}: JoinLobbyCardProps) {

	const { t } = useTranslation()

	const [code, setCode] = useState("")

	const handleJoin = () => {

		const normalizedCode = code.trim().toUpperCase()

		if (!normalizedCode)
			return

		onJoin(normalizedCode)
	}

	return (
		<div className="absolute top-0 left-1/2 -translate-x-1/2 z-50 w-full flex justify-center">
			<Card
				titleKey="lobby.buttons.join_lobby"
				isOpen={isOpen}
				onClose={onClose}
				footer={
					<div className="flex justify-center gap-4 w-full">

						<Button
							type="button"
							variant="ghost"
							onClick={onClose}
						>
							{t("button.cancel")}
						</Button>

						<Button
							type="button"
							variant="primary"
							onClick={handleJoin}
							disabled={!code.trim()}
						>
							{t("lobby.buttons.join")}
						</Button>

					</div>
				}
			>
				<form
					className="w-full flex flex-col gap-5"
					onSubmit={(e) => {
						e.preventDefault()
						handleJoin()
					}}
				>

					<Input
						labelKey="lobby.join.lobby_code"
						placeHolderKey="lobby.join.enter_code"
						value={code}
						onChange={(e) => setCode(e.target.value)}
					/>

				</form>
			</Card>
		</div>
	)
}

export default JoinLobbyCard