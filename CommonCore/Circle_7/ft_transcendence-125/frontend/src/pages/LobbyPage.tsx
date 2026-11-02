import Nav from "@/components/ui/Nav"
import Button from "@/components/ui/Button"
import Spinner from "@/components/ui/Spinner"
import Dropdown from "@/components/ui/Dropdown"

import PrivateLayout from "@/components/layouts/PrivateLayout"
import LobbyLayout from "@/components/lobby/LobbyLayout"

import ProfileCard from "@/components/home/ProfileCard";
import FriendsCard from "@/components/home/FriendsCard";
import RulesCard from "@/components/home/RulesCard"
import LeaderboardCard from "@/components/home/LeaderboardCard";
import LogoutModal from "@/components/home/LogoutModal";

import {useLobby} from "@/hooks/useLobby"
import {useEffect, useState} from "react"
import {useAuth} from "@/hooks/useAuth"
import {useNavigate, useParams} from "react-router-dom"
import {useTranslation} from "react-i18next"



function LobbyPage() {

	const { t, i18n } = useTranslation()
	const navigate = useNavigate()
	const { lobbyId } = useParams<{ lobbyId: string }>()
	const { user } = useAuth()

	const [language, setLanguage] = useState('dropdown.en')

	const languageOptions = [
		{ labelKey: "dropdown.en", onClick: () => {setLanguage('EN'); i18n.changeLanguage('en')} },
		{ labelKey: "dropdown.fr", onClick: () => {setLanguage('FR'); i18n.changeLanguage('fr')} },
		{ labelKey: "dropdown.es", onClick: () => {setLanguage('ES'); i18n.changeLanguage('es')} },
    ]

	// NAV
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

	// LOBBY
	const {
		lobby,
		loading,
		error,
		leaving,
		loadLobby,
		handleLeave,
		handleReady,
		handleSetColor,
		handleStartGame,
	} = useLobby(lobbyId)

	useEffect(() => {
		if (!lobby)
			return
		sessionStorage.setItem("currentLobbyId", lobby.id)
		sessionStorage.setItem("currentLobbyName", lobby.name)
	}, [lobby,])

return (
	<PrivateLayout>

		<div className="min-h-screen flex flex-col">
			<div
			>
				<Nav
					items={[
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


			<main className="flex-1 flex items-center justify-center px-2">

				<div className="flex w-full max-w-7xl items-center justify-center gap-6">

					{loading && (
						<div className="flex flex-col items-center gap-4 text-info">
							<Spinner
								size="sm"
								variant="light"
							/>

							<p>
								Loading lobby...
							</p>
						</div>
					)}


					{!loading && error && (
						<div className="flex flex-col items-center gap-5 text-center">

							<p className="text-warning">
								{error}
							</p>

							<Button
								variant="secondary"
								onClick={() =>
									void loadLobby()
								}
							>
								{t("lobby.buttons.retry")}
							</Button>

							<Button
								variant="ghost"
								onClick={() =>
									navigate("/selection")
								}
							>
								{t("lobby.buttons.back_lobby")}
							</Button>

						</div>
					)}


					{!loading && !error && lobby && (
						<LobbyLayout
							lobby={lobby}
							currentUserId={user!.id}
							leaving={leaving}
							onReady={handleReady}
							onLeave={handleLeave}
							onSetColor={handleSetColor}
							onStartGame={handleStartGame}
						/>
					)}

				</div>

			</main>


			<footer className="flex justify-center gap-6 py-4 text-info">

				<Button
					variant="ghost"
					onClick={() =>
						navigate("/terms")
					}
				>
					{t("terms.terms_of_service")}
				</Button>

				<Button
					variant="ghost"
					onClick={() =>
						window.open(
							"/policy",
							"_blank",
						)
					}
				>
					{t("terms.privacy_policy")}
				</Button>

			</footer>


			<ProfileCard
				isOpen={profileOpen}
				onClose={() =>
					setProfileOpen(false)
				}
			/>

			<FriendsCard
				isOpen={friendsOpen}
				onClose={() => setFriendsOpen(false)}
			/>

			<RulesCard
				isOpen={rulesOpen}
				onClose={() =>
					setRulesOpen(false)
				}
			/>

			<LeaderboardCard
				isOpen={leaderboardOpen}
				onClose={() =>
					setLeaderboardOpen(false)
				}
			/>

			<LogoutModal
				isOpen={logoutOpen}
				onClose={() =>
					setLogoutOpen(false)
				}
			/>

		</div>

	</PrivateLayout>
)
}

export default LobbyPage
