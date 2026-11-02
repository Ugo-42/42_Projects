import Button from "@/components/ui/Button"
import type { Lobby } from "@/types/lobby"

import { useTranslation } from "react-i18next"

type LobbyCardProps = {
	lobby: Lobby
	onJoin: (lobby: Lobby) => void
}

function LobbyCard({ lobby, onJoin }: LobbyCardProps) {

	const { t } = useTranslation()

	const isFull = lobby.players.length >= lobby.maxPlayers

	return (
		<div className="flex items-center justify-between gap-4 p-4 border border-info rounded-lg">

			<div className="min-w-0">
				<h3 className="font-semibold truncate">
					{lobby.name}
				</h3>

				<p className="text-sm opacity-70">
					{t("lobby.owner")}
				</p>
			</div>

			<div className="flex items-center gap-4 shrink-0">

				<span className="text-sm">
					{lobby.players.length}/{lobby.maxPlayers}
				</span>

				<Button
					variant="primary"
					disabled={isFull}
					onClick={() => onJoin(lobby)}
				>
					{isFull ? t("lobby.buttons.full") : t("lobby.buttons.join")}
				</Button>

			</div>

		</div>
	)
}

export default LobbyCard