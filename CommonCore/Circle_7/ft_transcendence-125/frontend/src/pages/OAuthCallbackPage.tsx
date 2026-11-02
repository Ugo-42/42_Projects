import { useEffect } from 'react'
import { useNavigate, useSearchParams } from 'react-router-dom'
import Spinner from '@/components/ui/Spinner'
import { getCurrentUser } from '@/services/authService'
import { connectSocket } from '@/services/socketService'
import { useAuth } from '@/hooks/useAuth'

function OAuthCallbackPage() {
	const navigate = useNavigate()
	const [searchParams] = useSearchParams()
	const { refreshUser } = useAuth()

	useEffect(() => {
		const accessToken = searchParams.get('accessToken')
		const refreshToken = searchParams.get('refreshToken')

		if (!accessToken || !refreshToken) {
			navigate('/', { replace: true })
			return
		}

		localStorage.setItem('token', accessToken)
		localStorage.setItem('refreshToken', refreshToken)

		void getCurrentUser()
			.then(async () => {
				await refreshUser()
				connectSocket()
				navigate('/home', { replace: true })
			})
			.catch(() => {
				localStorage.removeItem('token')
				localStorage.removeItem('refreshToken')
				navigate('/', { replace: true })
			})
	}, [navigate, refreshUser, searchParams])

	return <Spinner size="lg" variant="light" />
}

export default OAuthCallbackPage