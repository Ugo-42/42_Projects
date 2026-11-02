import { createContext, useCallback, useEffect, useState } from "react"
import { clearSession, getCurrentUser } from "@/services/authService"
import type { User } from "@/types/authTypes"
import {leaveCurrentLobby,} from "@/services/lobbyService"


type AuthContextType = {
	user: User | null
	loading: boolean
	isAuthenticated: boolean
	refreshUser: () => Promise<void>
	logoutLocal: () => void
}


export const AuthContext = createContext<AuthContextType | undefined>(undefined)


type Props = {
	children: React.ReactNode
}


export function AuthProvider({ children }: Props) {

	const [user, setUser] = useState<User | null>(null)
	const [loading, setLoading] = useState(true)


	const refreshUser = useCallback(async () => {

		const token = localStorage.getItem("token")
		if (!token) {
			setUser(null)
			return
		}
		try {
			const currentUser = await getCurrentUser()
			setUser(currentUser)
		} catch {

			try { await leaveCurrentLobby() } catch (error) {
				console.error("[AUTH] ailed to leave current lobby:", error)
			}
			clearSession()
			setUser(null)
		}
	}, [])


	const logoutLocal = useCallback(() => {
		clearSession()
		setUser(null)
	}, [])


	useEffect(() => {
		const initAuth = async () => {
			try {
				await refreshUser()
			} finally {
				setLoading(false)
			}
		}
		void initAuth()
	}, [refreshUser])


	return (
		<AuthContext.Provider value={{
			user,
			loading,
			isAuthenticated: !!user,
			refreshUser,
			logoutLocal,
		}}>
			{children}
		</AuthContext.Provider>
	)
}