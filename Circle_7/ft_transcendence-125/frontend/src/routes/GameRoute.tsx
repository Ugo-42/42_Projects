import Spinner from "@/components/ui/Spinner"
import { Navigate } from "react-router-dom"
import { useAuth } from "@/hooks/useAuth"


type GameRouteProps = {
	children: React.ReactNode
}


function GameRoute({ children }: GameRouteProps) {

	const {
		loading,
		isAuthenticated,
	} = useAuth()
	const inGame = sessionStorage.getItem("inGame")
	const currentGameId = sessionStorage.getItem("currentGameId")
	
	if (loading) {
		return (
			<div className="bg-black min-h-screen flex items-center justify-center">
				<Spinner size="sm" variant="light" />
			</div>
		)
	}

	if (!isAuthenticated) {
		return <Navigate to="/" replace />
	}

	if (!inGame || !currentGameId ) {
		return <Navigate to="/home" replace />
	}

	return children
}


export default GameRoute