import Spinner from "@/components/ui/Spinner"
import { Navigate } from "react-router-dom"
import { useAuth } from "@/hooks/useAuth"

type ProtectedRouteProps = {
	children: React.ReactNode
}

function ProtectedRoute({ children }: ProtectedRouteProps) {

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
	
	if (!isAuthenticated) {
		return <Navigate to="/" replace />
	}
	return children
}

export default ProtectedRoute