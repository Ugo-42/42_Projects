import { useState } from "react"
import { useTranslation } from "react-i18next"

import Button from "@/components/ui/Button"
import Input from "@/components/ui/Input"
import Card from "@/components/ui/Card"

type CreateLobbyCardProps = {
	isOpen: boolean
	onClose: () => void
	onCreate: (name: string, isPrivate: boolean) => void
}

function CreateLobbyCard({
	isOpen,
	onClose,
	onCreate,
}: CreateLobbyCardProps) {

	const { t } = useTranslation()

	const [name, setName] = useState("")
	const [isPrivate, setIsPrivate] = useState(false)

	const handleCreate = () => {
		if (!name.trim())
			return

		onCreate(name.trim(), isPrivate)
	}

	return (
		<div className="absolute top-0 left-1/2 -translate-x-1/2 z-50 w-full flex justify-center">
			<Card
				titleKey="lobby.buttons.create"
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
							onClick={handleCreate}
							disabled={!name.trim()}
						>
							{t("button.create")}
						</Button>

					</div>
				}
			>
				<form
					className="w-full flex flex-col gap-5"
					onSubmit={(e) => {
						e.preventDefault()
						handleCreate()
					}}
				>

					<Input
						labelKey="lobby.creation.lobby_name"
						placeHolderKey="lobby.creation.enter_name"
						value={name}
						onChange={(e) => setName(e.target.value)}
					/>

					<div className="flex justify-center gap-6 text-info">

						<label className="flex items-center gap-2">
							<input
								type="radio"
								name="visibility"
								checked={!isPrivate}
								onChange={() => setIsPrivate(false)}
							/>
							{t("lobby.creation.public")}
						</label>

						<label className="flex items-center gap-2">
							<input
								type="radio"
								name="visibility"
								checked={isPrivate}
								onChange={() => setIsPrivate(true)}
							/>
							{t("lobby.creation.private")}
						</label>

					</div>

				</form>
			</Card>
		</div>
	)
}

export default CreateLobbyCard