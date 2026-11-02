import Nav from "@/components/ui/Nav"
import Button from "@/components/ui/Button"
import Dropdown from "@/components/ui/Dropdown"

import PrivateLayout from "@/components/layouts/PrivateLayout"

import ProfileCard from "@/components/home/ProfileCard"
import RulesCard from "@/components/home/RulesCard"
import FriendsCard from "@/components/home/FriendsCard"
import LeaderboardCard from "@/components/home/LeaderboardCard"
import LogoutModal from "@/components/home/LogoutModal"

import LobbyList from "@/components/lobby/LobbyList"
import CreateLobbyCard from "@/components/lobby/CreateLobbyCard"
import JoinLobbyCard from "@/components/lobby/JoinLobbyCard"

import {
	getPublicLobbies,
	createLobby,
	joinPublicLobby,
	joinLobbyByCode,
} from "@/services/lobbyService"

import type { Lobby } from "@/types/lobby"

import { useEffect, useState } from "react"
import { useNavigate } from "react-router-dom"
import { useTranslation } from "react-i18next"


function LobbySelectionPage() {

	const { t, i18n } = useTranslation()
	const navigate = useNavigate()
	const [language, setLanguage] = useState('dropdown.en')

	const languageOptions = [
		{ labelKey: "dropdown.en", onClick: () => {setLanguage('EN'); i18n.changeLanguage('en')} },
		{ labelKey: "dropdown.fr", onClick: () => {setLanguage('FR'); i18n.changeLanguage('fr')} },
		{ labelKey: "dropdown.es", onClick: () => {setLanguage('ES'); i18n.changeLanguage('es')} },
    ]

	// Nav
	const [navOpen, setNavOpen] = useState(false)
	const [profileOpen, setProfileOpen] = useState(false)
	const [friendsOpen, setFriendsOpen] = useState(false)
	const [rulesOpen, setRulesOpen] = useState(false)
	const [leaderboardOpen, setLeaderboardOpen] = useState(false)
	const [logoutOpen, setLogoutOpen] = useState(false)
	const [languageOpen, setLanguageOpen] = useState(false)
	const closeAllCards = () => {
		setProfileOpen(false)
		setFriendsOpen(false)
		setRulesOpen(false)
		setLeaderboardOpen(false)
		setLogoutOpen(false)
		setLanguageOpen(false)
	}

	const openProfile = () => {closeAllCards()
		setProfileOpen(true)}
	const openFriends = () => {closeAllCards()
		setFriendsOpen(true)}
	const openRules = () => {closeAllCards()
		setRulesOpen(true)}
	const openLeaderboard = () => {closeAllCards() 
		setLeaderboardOpen(true)}
	const openLogout = () => {closeAllCards()
		setLogoutOpen(true)}
	const toggleLanguage = () => {
		const shouldOpen = !languageOpen
		closeAllCards()
		if (shouldOpen) {
			setLanguageOpen(true)
		}
	}

	// Lobby
	const [createOpen, setCreateOpen] = useState(false)
	const [joinOpen, setJoinOpen] = useState(false)

	const [lobbies, setLobbies] = useState<Lobby[]>([])
	const [loading, setLoading] = useState(true)
	const [error, setError] = useState<string | null>(null)

	useEffect(() => {
		loadLobbies()
	}, [])

	const loadLobbies = async () => {

		try {

			setLoading(true)
			setError(null)

			const result = await getPublicLobbies()

			setLobbies(result)

		} catch (error) {

			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to load lobbies")
			}

		} finally {

			setLoading(false)
		}
	}

	const handleCreateLobby = async (
		name: string,
		isPrivate: boolean,
	) => {

		try {

			setError(null)

			const lobby = await createLobby({
				name,
				isPrivate,
			})

			setCreateOpen(false)

			navigate(`/lobby/${lobby.id}`)

		} catch (error) {

			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to create lobby")
			}
		}
	}


	const handleJoinByCode = async (
		code: string,
	) => {

		try {

			setError(null)

			const lobby = await joinLobbyByCode(code)

			setJoinOpen(false)

			navigate(`/lobby/${lobby.id}`)

		} catch (error) {

			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to join lobby")
			}
		}
	}


	const handleJoinLobby = async (
		lobby: Lobby,
	) => {

		try {

			setError(null)

			const joinedLobby =
				await joinPublicLobby(lobby.id)

			navigate(`/lobby/${joinedLobby.id}`)

		} catch (error) {

			if (error instanceof Error) {
				setError(error.message)
			} else {
				setError("Unable to join lobby")
			}
		}
	}


	const openCreate = () => {
		setCreateOpen(true)
		setJoinOpen(false)
		setError(null)
	}


	const openJoin = () => {
		setJoinOpen(true)
		setCreateOpen(false)
		setError(null)
	}


	return (
		<PrivateLayout>

			<div className="min-h-screen flex flex-col">
						<div
			>
				<Nav
					items={[
					{
						labelKey: "nav.home",
						onClick: () => navigate("/home"),
					},
					{
						labelKey: "nav.profile",
						onClick: () => openProfile(),
					},
					{
						labelKey: "nav.friends",
						onClick: () => openFriends(),
					},
					{
						labelKey: "nav.rules",
						onClick: () => openRules(),
					},
					{
						labelKey: "nav.languages",
						onClick: () => toggleLanguage(),
					},
					{
						labelKey: "nav.leaderboard",
						onClick: () => openLeaderboard(),
					},
					{
						labelKey: "nav.logout",
						onClick: () => openLogout(),
					},]} 
					isOpen={navOpen}
					onToggle={() => {
						setNavOpen(!navOpen)
						setLanguageOpen(false)
					}}/>
			</div>
			
			{languageOpen && (
				<div className="fixed top-54 left-[130px] z-50">
					<Dropdown
						options={languageOptions}
						selectedKey={language}
						variant="info"
						align="right"
					/>
				</div>
			)}


				<main className="flex-1 flex items-center justify-center px-4 py-8">

					<div className="flex flex-col items-center gap-6 w-full max-w-5xl">

						<h1 className="text-3xl font-bold">
							{t("lobby.buttons.lobby")}
						</h1>


						<div className="flex gap-4">

							<Button
								variant="primary"
								onClick={openCreate}
							>
								{t("lobby.buttons.create")}
							</Button>

							<Button
								variant="secondary"
								onClick={openJoin}
							>
								{t("lobby.buttons.join_code")}
							</Button>

						</div>


						{error && (
							<div className="text-red-500 text-center">
								{error}
							</div>
						)}


						<div className="relative w-full flex flex-col items-center gap-6">

							<CreateLobbyCard
								isOpen={createOpen}
								onClose={() => setCreateOpen(false)}
								onCreate={handleCreateLobby}
							/>


							<JoinLobbyCard
								isOpen={joinOpen}
								onClose={() => setJoinOpen(false)}
								onJoin={handleJoinByCode}
							/>

							{loading ? (

								<div className="text-info font-micro-5">
									Loading lobbies...
								</div>

							) : (
							
								<LobbyList
									lobbies={lobbies}
									onJoin={handleJoinLobby}
								/>

							)}
							<div className="flex items-center justify-between gap-4">
								<Button
									onClick={() => void loadLobbies()}
									disabled={loading}
								>
									{loading ? "Refreshing..." : t("lobby.buttons.refresh")}
								</Button>
							</div>

						</div>

					</div>

				</main>


				<footer className="flex justify-center gap-6 py-4 text-info">

					<Button
						variant="ghost"
						onClick={() => navigate("/terms")}
					>
						{t("terms.terms_of_service")}
					</Button>

					<Button
						variant="ghost"
						onClick={() => navigate("/policy")}
					>
						{t("terms.privacy_policy")}
					</Button>

				</footer>


				<ProfileCard
					isOpen={profileOpen}
					onClose={() => setProfileOpen(false)}
				/>

				<FriendsCard
					isOpen={friendsOpen}
					onClose={() => setFriendsOpen(false)}
				/>

				<RulesCard
					isOpen={rulesOpen}
					onClose={() => setRulesOpen(false)}
				/>

				<LeaderboardCard
					isOpen={leaderboardOpen}
					onClose={() => setLeaderboardOpen(false)}
				/>

				<LogoutModal
					isOpen={logoutOpen}
					onClose={() => setLogoutOpen(false)}
				/>

			</div>

		</PrivateLayout>
	)
	
}


export default LobbySelectionPage