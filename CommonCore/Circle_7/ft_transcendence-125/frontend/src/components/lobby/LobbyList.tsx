import type { Lobby } from "@/types/lobby"
import LobbyCard from "./LobbyCard"

import { useTranslation } from "react-i18next"

type LobbyListProps = {
	lobbies: Lobby[]
	onJoin: (lobby: Lobby) => void
}

function LobbyList({
	lobbies,
	onJoin,
}: LobbyListProps) {

	const { t } = useTranslation()

	return (
		<div className="w-full max-w-3xl">

			<div className="border border-info rounded-xl p-6">

				<h2 className="font-micro-5 text-info text-xl font-semibold text-center mb-6">
					{t("lobby.buttons.public")}
				</h2>

				{lobbies.length === 0 ? (

					<div className="font-micro-5 text-info text-center py-10 text-lg">
						{t("lobby.no_public")}
						<p className="font-micro-5 text-info text-lg mt-2">
							{t("lobby.create_invite")}
						</p>
					</div>

				) : (

					<div className="font-micro-5 text-info flex flex-col gap-3">

						{lobbies.map((lobby) => (
							<LobbyCard
								key={lobby.id}
								lobby={lobby}
								onJoin={onJoin}
							/>
						))}

					</div>

				)}

			</div>

		</div>
	)
}

export default LobbyList