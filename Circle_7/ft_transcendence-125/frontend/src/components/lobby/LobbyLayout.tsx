import Button from "../ui/Button"
import Spinner from "../ui/Spinner"

import type {
	Lobby,
	LobbyPlayer,
} from "@/types/lobby"

import type { CharacterColor } from "@/components/game/config/characterConfig"

import { useState } from "react"
import { useTranslation } from "react-i18next"


const LOBBY_COLORS: CharacterColor[] = [
	'blue', 'cyan', 'green', 'orange', 'yellow', 'red', 'pink', 'purple',
]

const COLOR_SWATCH: Record<CharacterColor, string> = {
	blue: '#3b82f6',
	cyan: '#22d3ee',
	green: '#22c55e',
	orange: '#f97316',
	yellow: '#eab308',
	red: '#ef4444',
	pink: '#ec4899',
	purple: '#a855f7',
}


type LobbyLayoutProps = {
	lobby: Lobby
	currentUserId: number
	leaving?: boolean
	onReady: (ready: boolean) => Promise<void> | void
	onLeave: () => Promise<void> | void
	onStartGame: () => Promise<void> | void
	onSetColor: (color: string) => Promise<void> | void
}


function LobbyLayout({
	lobby,
	currentUserId,
	leaving = false,
	onReady,
	onLeave,
	onStartGame,
	onSetColor,
}: LobbyLayoutProps) {

	const { t } = useTranslation()

	const [readyLoading, setReadyLoading] = useState(false)
	const [startLoading, setStartLoading] = useState(false)
	const [colorLoading, setColorLoading] = useState(false)

	const currentPlayer = lobby.players.find(
		(player) => player.userId === currentUserId,
	)

	const isOwner = lobby.ownerId === currentUserId
	const isReady = currentPlayer?.ready ?? false
	const isWaiting = lobby.status === "WAITING"

	const canStart = (
		isOwner &&
		isWaiting &&
		lobby.players.length >= 2
	)

	const takenColors = new Set(
		lobby.players
			.filter((p) => p.userId !== currentUserId)
			.map((p) => p.color)
			.filter((c): c is string => c !== null),
	)

	const emptySlots = Math.max(
		0,
		lobby.maxPlayers - lobby.players.length,
	)


	const handleReady = async () => {

		if (!currentPlayer || readyLoading)
			return

		try {
			setReadyLoading(true)
			await onReady(!isReady)
		} finally {
			setReadyLoading(false)
		}
	}


	const handleStartGame = async () => {

		if (!isOwner || startLoading)
			return

		try {
			setStartLoading(true)
			await onStartGame()
		} finally {
			setStartLoading(false)
		}
	}


	const handlePickColor = async (
		color: CharacterColor,
	) => {

		if (!currentPlayer || colorLoading || !isWaiting)
			return

		if (currentPlayer.color === color)
			return

		try {
			setColorLoading(true)
			await onSetColor(color)
		} finally {
			setColorLoading(false)
		}
	}


	return (
		<div className="w-full max-w-2xl min-h-[550px] max-h-[70vh] bg-black border-2 border-info rounded-2xl p-9 flex flex-col">

			<h1 className="text-5xl text-center font-micro-5 text-info mb-6">
				{lobby.name}
			</h1>

			<div className="text-center mb-8">
				{lobby.isPrivate && lobby.code && (
					<p className="text-warning text-3xl font-micro-5 mt-2">
						{t("lobby.info.code")} {lobby.code}
					</p>
				)}
				<p className="text-info/70 text-sm mt-2">
					{lobby.players.length}/{lobby.maxPlayers}  {t("lobby.info.players")}
				</p>
			</div>
			{currentPlayer && isWaiting && (
				<div className="flex flex-col items-center gap-2 mb-6">
					<span className="text-info/70 text-sm">
						{t("lobby.info.pick_color")}
					</span>
					<div className="flex gap-2">
						{LOBBY_COLORS.map((color) => {
							const isTaken = takenColors.has(color)
							const isSelected = currentPlayer.color === color

							return (
								<button
									key={color}
									onClick={() => void handlePickColor(color)}
									disabled={colorLoading || (isTaken && !isSelected)}
									title={color}
									className={`w-8 h-8 rounded-full border-2 transition-opacity disabled:cursor-not-allowed ${
										isSelected
											? 'border-white opacity-100'
											: isTaken
												? 'border-white/10 opacity-25'
												: 'border-white/30 opacity-70 hover:opacity-100'
									}`}
									style={{ backgroundColor: COLOR_SWATCH[color] }}
								/>
							)
						})}
					</div>
				</div>
			)}

			<div className="flex-1 flex flex-col gap-6 overflow-y-auto">

				{lobby.players.map(
					(player: LobbyPlayer) => {

						const playerIsOwner = player.userId === lobby.ownerId
						const playerIsCurrentUser = player.userId === currentUserId
						const swatchColor = player.color
							? COLOR_SWATCH[player.color as CharacterColor]
							: null

						return (
							<div key={player.id} className="flex justify-between items-center border-b border-info pb-3 gap-4">
								<div className="flex items-center gap-2 min-w-0">
									{swatchColor && (
										<span
											className="w-4 h-4 rounded-full border border-white/30 shrink-0"
											style={{ backgroundColor: swatchColor }}
										/>
									)}
									<span className="text-primary font-micro-5 text-xl truncate">
										👤 {player.username}
									</span>
									{playerIsCurrentUser && (
										<span className="text-xs text-info/60">
											{t("lobby.info.you")}
										</span>
									)}
								</div>
								<div className="flex items-center gap-3 shrink-0">
									{playerIsOwner && (
										<span className="text-info font-micro-5">
											{t("lobby.info.host")}
										</span>
									)}
									{player.ready ? (
										<span className="text-success font-micro-5">
											{t("lobby.info.ready")}
										</span>
									) : (
										<span className="text-warning font-micro-5">
											{t("lobby.info.not_ready")}
										</span>
									)}
								</div>
							</div>
						)
					},
				)}


				{Array.from({ length: emptySlots }).map((_, index) => (

					<div key={`empty-${index}`} className="flex justify-between items-center border-b border-info pb-3">

						<span className="text-primary/50">
							{t("lobby.info.vacant")}
						</span>
					</div>

				))}

			</div>


			<div className="flex flex-wrap justify-center gap-6 pt-8">

				<Button
					className="px-8 py-3 text-2xl"
					variant={isReady ? "warning" : "success"}
					onClick={() => void handleReady()}
					disabled={readyLoading || lobby.status !== "WAITING"}
				>
					{readyLoading ? (
						<Spinner size="sm" variant="light" />
					) : isReady ? (
						t("lobby.info.not_ready")
					) : (
						t("lobby.info.ready")
					)}
				</Button>


				{isOwner && (
					<Button
						className="px-8 py-3 text-2xl"
						variant="primary"
						onClick={() => void handleStartGame()}
						disabled={!canStart || startLoading}
					>
						{startLoading ? (
							<Spinner size="sm" variant="light" />
						) : (
							t("lobby.buttons.start")
						)}
					</Button>
				)}


				<Button
					className="px-8 py-3 text-2xl"
					variant="ghost"
					onClick={() => void onLeave()}
					disabled={leaving}
				>
					{leaving ? (
						<Spinner size="sm" variant="light" />
					) : (
						t("lobby.buttons.leave")
					)}
				</Button>

			</div>

		</div>
	)
}

export default LobbyLayout
