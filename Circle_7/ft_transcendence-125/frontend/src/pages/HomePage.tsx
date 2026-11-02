import Nav from "@/components/ui/Nav";
import Button from "@/components/ui/Button";
import PrivateLayout from "@/components/layouts/PrivateLayout";

import ProfileCard from "@/components/home/ProfileCard";
import RulesCard from "@/components/home/RulesCard";
import FriendsCard from "@/components/home/FriendsCard";
import LeaderboardCard from "@/components/home/LeaderboardCard";
import LogoutModal from "@/components/home/LogoutModal";
import Dropdown from "@/components/ui/Dropdown";

import { useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { useTranslation } from "react-i18next";

function HomePage() {

	const { t, i18n } = useTranslation()
	const navigate = useNavigate()

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

    const [language, setLanguage] = useState('dropdown.en')

	const languageOptions = [
		{ labelKey: "dropdown.en", onClick: () => {setLanguage('EN'); i18n.changeLanguage('en')} },
		{ labelKey: "dropdown.fr", onClick: () => {setLanguage('FR'); i18n.changeLanguage('fr')} },
		{ labelKey: "dropdown.es", onClick: () => {setLanguage('ES'); i18n.changeLanguage('es')} },
    ]

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
				<div className="fixed top-45 left-[130px] z-50">
					<Dropdown
						options={languageOptions}
						selectedKey={language}
						variant="info"
						align="right"
					/>
				</div>
			)}

			<main className="flex-1 flex flex-col items-center justify-center">

				<div className="text-center">
					<h1 className="text-8xl md:text-[175px] lg:text-[250px] font-micro-5 text-primary">
						BOMBERMAN
					</h1>
				</div>

				<div className="flex justify-center items-center mt-10">
					<Button onClick={() => navigate("/selection")}
						className="px-12 py-6 text-5xl md:text-6xl lg:text-7xl">
						{t("play")}
					</Button>
				</div>
		</main>
			<footer className="flex justify-center gap-6 py-4 text-info">
				<Button variant="ghost" onClick={() => navigate("/terms")}>
					{t("terms.terms_of_service")}
				</Button>
				<Button variant="ghost" onClick={() => navigate("/policy")}>
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
);
}

export default HomePage;