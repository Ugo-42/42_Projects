import {
	createContext,
	useCallback,
	useEffect,
	useState,
} from "react"

import { connectSocket, getAppSocket } from "@/services/socketService"
import { useAuth } from "@/hooks/useAuth"

type PresenceByUser =
	Record<number, boolean>

type PresenceContextType = {
	presenceByUser: PresenceByUser
	isOnline: (userId: number) => boolean
	fetchPresence: (userIds: number[]) => void
}

export const PresenceContext =
	createContext<
		PresenceContextType | undefined
	>(undefined)

type PresenceProviderProps = {children: React.ReactNode}

export function PresenceProvider({
	children,
}: PresenceProviderProps) {

	const { user } = useAuth()
	
	const [presenceByUser,setPresenceByUser] = useState<PresenceByUser>({})

	const fetchPresence =
		useCallback((userIds: number[],) => {
			const socket =getAppSocket()
			if (!socket)
				return
			if (userIds.length === 0)
				return

			socket.emit("presence:get", {userIds},
				(response: {
					success: boolean
					statuses?: PresenceByUser
				}) => {
					if (!response?.success || !response.statuses)
						return
					setPresenceByUser(
						(previous) => ({
							...previous,
							...response.statuses,
						}),
					)
				},
			)
		}, [])

	const isOnline =
		useCallback((userId: number) => {
			return (presenceByUser[userId] ?? false)
		}, [presenceByUser])

	useEffect(() => {

		if (!user) {
			setPresenceByUser({})
			return
		}
		connectSocket()
		const socket =getAppSocket()
		if (!socket)
			return

		const handleOnline = (payload: {userId: number},
		) => {setPresenceByUser(
				(previous) => ({
					...previous,
					[payload.userId]: true,
				}),
			)
		}

		const handleOffline = (payload: {userId: number},
		) => {
			setPresenceByUser((previous) => ({
					...previous,
					[payload.userId]: false,
				}),
			)
		}
		socket.on("user:online",handleOnline)
		socket.on("user:offline",handleOffline)

		return () => {
			socket.off("user:online", handleOnline)
			socket.off("user:offline",handleOffline)
		}

	}, [user])

	return (
		<PresenceContext.Provider
			value={{presenceByUser, isOnline, fetchPresence}}
		>
			{children}
		</PresenceContext.Provider>
	)
}