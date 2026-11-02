import { Navigate } from "react-router-dom"

import Spinner from "@/components/ui/Spinner"

import { useAuth } from "@/hooks/useAuth"

type Props = {
	children: React.ReactNode
}

function GameLayout({ children }: Props) {

	const {
		loading,
		isAuthenticated,
	} = useAuth()

	if (loading) {
		return (
			<div className="bg-black min-h-screen flex items-center justify-center">
				<Spinner size="sm" variant="light" />
			</div>
		)
	}

	if (!isAuthenticated) {
		return (
			<Navigate
				to="/"
				replace
			/>
		)
	}

	return (
		<div className="bg-black min-h-screen flex flex-col">
			{children}
		</div>
	)
}

export default GameLayout