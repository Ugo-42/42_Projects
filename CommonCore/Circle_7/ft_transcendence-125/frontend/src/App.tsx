import { Routes, Route } from 'react-router-dom'
import HomePage from './pages/HomePage'
import GamePage from './pages/GamePage'
import LandingPage from './pages/LandingPage'
import TermsPage from './pages/TermsPage'
import TestPage from './pages/TestPage'
import PrivacyPage from './pages/PrivacyPage'
import LobbyPage from './pages/LobbyPage'
import LobbySelectionPage from './pages/LobbySelectionPage'
import ProtectedRoute from "@/routes/ProtectedRoute"
import PublicRoute from './routes/PublicRoute'
import GameRoute from './routes/GameRoute'
import OAuthCallbackPage from './pages/OAuthCallbackPage'
import { useEffect } from "react"

import {
	connectSocket,
} from "@/services/socketService"


function App() {

	useEffect(() => {

		const token =
			localStorage.getItem("token")

		if (token) {
			connectSocket()
		}

	}, [])


	return (
		<Routes>
			<Route path="/oauth/callback" element={<OAuthCallbackPage />} />
			<Route path="/terms" element={<TermsPage />} />
			<Route path="/policy" element={<PrivacyPage />} />
			<Route path="/test" element={<TestPage />} />

			<Route
				path="/"
				element={
					<PublicRoute>
						<LandingPage />
					</PublicRoute>
				}
			/>

			<Route
				path="/home"
				element={
					<ProtectedRoute>
						<HomePage />
					</ProtectedRoute>
				}
			/>

			<Route
				path="/selection"
				element={
					<ProtectedRoute>
						<LobbySelectionPage />
					</ProtectedRoute>
				}
			/>

			<Route
				path="/lobby/:lobbyId"
				element={
					<ProtectedRoute>
						<LobbyPage />
					</ProtectedRoute>
				}
			/>

			<Route
				path="/game"
				element={
					<GameRoute>
						<GamePage />
					</GameRoute>
				}
			/>
		</Routes>
	)
}

export default App