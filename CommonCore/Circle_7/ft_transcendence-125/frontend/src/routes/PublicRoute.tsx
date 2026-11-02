import Spinner from "@/components/ui/Spinner"
import { Navigate } from "react-router-dom"
import { useAuth } from "@/hooks/useAuth"


type PublicRouteProps = {
	children: React.ReactNode
}


function PublicRoute({ children }: PublicRouteProps) {

	const {
		loading,
		isAuthenticated,
	} = useAuth()

	if (loading) {
		return (
			<div className="min-h-screen flex items-center justify-center">
				<Spinner size="sm" variant="light" />
			</div>
		)
	}
	
	if (isAuthenticated) {
		return <Navigate to="/home" replace />
	}
	return children
}


export default PublicRoute