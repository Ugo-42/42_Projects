import { Navigate } from "react-router-dom"

import Spinner from "@/components/ui/Spinner"
import ChatBubble from "@/components/layouts/ChatBubble"

import { useAuth } from "@/hooks/useAuth"


type Props = {
	children: React.ReactNode
}


function PrivateLayout({ children }: Props) {

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

			<ChatBubble />
		</div>
	)
}


export default PrivateLayout