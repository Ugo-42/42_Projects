import Button from '../ui/Button'
import Input from '../ui/Input'
import Card from '../ui/Card'
import Spinner from '../ui/Spinner'
import SocialLogin from './SocialLogin'

import { useState } from 'react'
import { useNavigate } from "react-router-dom"
import { register } from '@/services/authService'
import { validateRegister } from '@/utils/validation'
import { useTranslation } from 'react-i18next'
import { useAuth } from '@/hooks/useAuth'


type RegisterCardProps = {
	isOpen: boolean
	onClose: () => void
	onLogin: () => void
}

function RegisterCard({
	isOpen,
	onClose,
	onLogin,
}: RegisterCardProps) {

	const { t } = useTranslation()
	const navigate = useNavigate()

	const [loading, setLoading] = useState(false)
	const [username, setUserName] = useState("")
	const [email, setEmail] = useState("")
	const [password, setPassword] = useState("")
	const [confirmPassword, setConfirmPassword] = useState("")
	const [error, setError] = useState("")
	const { refreshUser } = useAuth()

	const handleRegister = async (e: React.FormEvent<HTMLFormElement>) => 
	{
		e.preventDefault()
		setLoading(true)
		setError("")
		try {
			const validationError = validateRegister(
				{
					username,
					email,
					password,
				},
				confirmPassword,
			)
			if (validationError) {
				setError(validationError)
				return
			}
			const result = await register({
				username,
				email,
				password,
			})
			await refreshUser()
			if (result.accessToken) {
				navigate("/home")
			} else {
				setError("Unable to create account.")
			}
		}
		finally {
			setLoading(false)
		}
	}

	if (!isOpen)
		return null

	return (
		
		<div className="fixed inset-0 z-40 overflow-y-auto">
			<div className="min-h-dvh flex items-center justify-center p-4">
				<Card
					className="gap-1"
					titleKey="auth.register"
					isOpen={isOpen}
					onClose={onClose}
					footer={
						<SocialLogin />
					}
				>
					<form 
						className="w-full max-w-md mx-auto px-4 pt-0 pb-1 flex flex-col gap-1"
						onSubmit={handleRegister}
					>

						{error && (
							<p className="text-error text-center text-sm">
								{error}
							</p>
						)}

						<Input
							labelKey="auth.username"
							value={username}
							onChange={(e) => setUserName(e.target.value)}
							placeHolderKey="auth.choose.choose_username"
						/>

						<Input
							labelKey="Email"
							value={email}
							onChange={(e) => setEmail(e.target.value)}
							placeHolderKey="auth.enter_email"
							type="email"
						/>

						<Input
							labelKey="auth.password"
							value={password}
							onChange={(e) => setPassword(e.target.value)}
							placeHolderKey="auth.choose.choose_password"
							type="password"
						/>

						<Input
							labelKey="auth.confirm_password"
							value={confirmPassword}
							onChange={(e) => setConfirmPassword(e.target.value)}
							placeHolderKey="auth.confirm_password"
							type="password"
						/>

						<div className="flex flex-col items-center gap-2 mt-5">
							<Button
								type="submit"
								variant="primary"
								className="w-2/3 sm:w-1/2"
								disabled={loading}
							>
								{loading ? (<Spinner size="sm" variant="light" />)
								: t('auth.register')}
							</Button>

							<Button
								type="button"
								variant="ghost"
								onClick={onLogin}
							>
								{t("auth.have_account")}
							</Button>
						</div>

					</form>
				</Card>
			</div>
		</div>
	)
}


export default RegisterCard