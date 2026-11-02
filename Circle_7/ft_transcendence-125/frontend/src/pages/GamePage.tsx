import Button from '../components/ui/Button'
import Modal from '../components/ui/Modal'
import Nav from '@/components/ui/Nav'

import GameLayout from '../components/layouts/GameLayout'
import RulesCard from '@/components/home/RulesCard'
import GameBoard from '../components/game/GameBoard'

import {
	useCallback,
	useEffect,
	useState,
	useRef
} from "react"
import { getMyProfile } from '@/api/profile'

import { useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'
import { leaveCurrentLobby } from "@/services/lobbyService"
import { getChatSocket } from "@/services/socketService"
import type { GameEndedPayload } from "@/services/gameSocketService"	

function GamePage() {

	const { t } = useTranslation()
	const navigate = useNavigate()

	const [navOpen, setNavOpen] = useState(false)
	const [exitModalOpen, setExitModalOpen] = useState(false)
	const [rulesOpen, setRulesOpen] = useState(false)

	const [gameEnded, setGameEnded] = useState<{
		winnerId: number | null
		winnerName: string | null
	} | null>(null)

	const [countdown, setCountdown] = useState(5)

	const myPlayerIdRef = useRef<number | null>(null)

	useEffect(() => {
		const loadMyProfile = async () => {
			try {
				const profile = await getMyProfile()

				console.log(
					"[GAME PAGE] My profile:",
					profile,
				)

				console.log(
					"[GAME PAGE] My player ID:",
					profile.id,
				)

				myPlayerIdRef.current = profile.id
			} catch (error) {
				console.error(
					"[GAME PAGE] Failed to get current profile:",
					error,
				)
			}
		}

		loadMyProfile()
	}, [])

	const closeRulesCards = () => {
		setRulesOpen(false)
	}

	const openRules = () => {
		closeRulesCards()
		setRulesOpen(true)
	}

	const returnToLobby = useCallback(() => {

		const lobbyId =
			sessionStorage.getItem("currentLobbyId")
		sessionStorage.removeItem("currentGameId")
		sessionStorage.removeItem("inGame")

		if (lobbyId) {
			navigate(
				`/lobby/${lobbyId}`,
				{ replace: true },
			)
			return
		}

		navigate(
			"/home",
			{ replace: true },
		)
	}, [navigate])

	const handleExitGame = async () => {

		try {
			await leaveCurrentLobby()
		} catch (error) {
			console.error(
				"[GAME] Failed to leave lobby:",
				error,
			)
			return
		}

		const lobbyId =
			sessionStorage.getItem("currentLobbyId")

		const chatSocket = getChatSocket()

		if (lobbyId && chatSocket) {
			chatSocket.emit(
				"chat:leave_room",
				`lobby:${lobbyId}`,
			)
		}

		sessionStorage.removeItem("currentLobbyId")
		sessionStorage.removeItem("currentLobbyName")
		sessionStorage.removeItem("currentGameId")
		sessionStorage.removeItem("inGame")
		setExitModalOpen(false)
		navigate("/home")
	}

	const handleGameEnded = useCallback((
		winnerId: number | null,
		winnerName: string | null,
		data: GameEndedPayload,
	) => {
		console.log("[GAME PAGE] Game ended:", {
			winnerId,
			winnerName,
			data,
		})
		setGameEnded({
			winnerId,
			winnerName,
		})

		const currentPlayerId = myPlayerIdRef.current

		console.log(
			"[GAME PAGE] My player ID:",
			currentPlayerId,
		)
		console.log(
			"[GAME PAGE] Players received:",
			data.players,
		)
		const me = data.players.find(
			(player) => player.id === currentPlayerId,
		)
		console.log(
			"[GAME PAGE] me:",
			me,
		)

		if (!me) {
			console.warn(
				"[GAME PAGE] Impossible de retrouver mon joueur",
				{
					myPlayerId: currentPlayerId,
					players: data.players,
				},
			)
			return
		}

		console.log("XP gagnée :", me.xp)
		console.log("Statistiques :", me.stats)

		console.log("Bombes :", me.stats.bombsPlaced)
		console.log("Blocs :", me.stats.blocksDestroyed)
		console.log("Kills :", me.stats.kills)
		console.log("Morts :", me.stats.deaths)
		console.log("Power-ups :", me.stats.powerUpsCollected)
	}, [])

	useEffect(() => {

		if (!gameEnded) {
			return
		}

		const interval =
			window.setInterval(() => {
				setCountdown(
					(previous) =>
						Math.max(previous - 1, 0),
				)
			}, 1000)

		const timeout =
			window.setTimeout(() => {
				returnToLobby()
			}, 5000)

		return () => {
			window.clearInterval(interval)
			window.clearTimeout(timeout)
		}
	}, [gameEnded, returnToLobby])

	const winnerText =
		gameEnded === null
		? ""
			: gameEnded.winnerName === null
			? "DRAW"
				: `${gameEnded.winnerName.toUpperCase()} WINS!`

	return (
		<GameLayout>
			<div className="min-h-screen flex flex-col">

				<header>
					<Nav
						items={[
							{
								labelKey: "nav.rules",
								onClick: () => openRules(),
							},
							{
								labelKey: "button.exit.quit",
								onClick: () => setExitModalOpen(true),
							},
						]}
						isOpen={navOpen}
						onToggle={() => {
							setNavOpen(!navOpen)
						}}
					/>
				</header>

				<main className="flex-1 flex items-center justify-center p-6">

					<div
						className="
							relative
							w-[90vw]
							h-[80vh]
							max-w-[1400px]
							border-2
							border-info
							rounded-2xl
							flex
							items-center
							justify-center
						"
					>

						<GameBoard
							onGameEnded={handleGameEnded}
						/>

						{gameEnded && (
							<div
								className="
									absolute
									inset-0
									z-30
									flex
									items-center
									justify-center
									bg-black/60
									rounded-2xl
								"
							>
								<div
									className="
										flex
										flex-col
										items-center
										justify-center
										gap-6
										min-w-[320px]
										p-10
										border-2
										border-info
										rounded-2xl
										bg-black/80
										text-center
										"
								>
									<h1
										className="
											text-5xl
											font-micro-5
											text-white
										"
									>
										{winnerText}
									</h1>

									<p className="text-xl text-white">
										Returning to lobby in{" "}
										<span className="font-bold">
											{countdown}
										</span>
									</p>

								<Button
									variant="ghost"
									onClick={returnToLobby}
								>
									Skip
								</Button>
							</div>
						</div>
					)}

					</div>

				</main>

				<Modal
					isOpen={exitModalOpen}
					onClose={() => setExitModalOpen(false)}
					footer={
						<>
							<Button
								variant="ghost"
								onClick={() =>
									setExitModalOpen(false)
								}
							>
								{t("button.cancel")}
							</Button>

							<Button
								variant="error"
								onClick={handleExitGame}
							>
								{t("button.exit.game")}
							</Button>
						</>
					}
				>
					<div className="lg:min-w-[350px] md:min-w-[150px] text-center">
						<h2 className="text-2xl font-micro-5 text-white">
							{t("questions.leave")}
						</h2>

						<p className="mt-4 text-white">
							{t("questions.really_sure")}
						</p>
					</div>
				</Modal>

				<RulesCard
					isOpen={rulesOpen}
					onClose={() => setRulesOpen(false)}
				/>

			</div>
		</GameLayout>
	)
}

export default GamePage
