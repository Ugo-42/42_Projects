import Button from '../ui/Button'
import Input from '../ui/Input'
import Card from "../ui/Card"
import Spinner from '../ui/Spinner'
import SocialLogin from './SocialLogin'

import { login, verifyTwoFactor } from '@/services/authService'
import { useState } from 'react'
import { useNavigate } from "react-router-dom"
import { useTranslation } from 'react-i18next'
import { useAuth } from '@/hooks/useAuth'

type LoginCardProps = {
	isOpen: boolean
	onClose: () => void
	onRegister: () => void
}

function maskEmail(email: string) {
	const [localPart, domain] = email.split('@')
	if (!localPart || !domain) return email
	return `${localPart.slice(0, 2)}${'*'.repeat(Math.max(3, localPart.length - 2))}@${domain}`
}

function LoginCard({
	isOpen,
	onClose,
	onRegister,
}: LoginCardProps) {

	const { t } = useTranslation()
	const navigate = useNavigate()

	const [loading, setLoading] = useState(false)
	const [identifier, setIdentifier] = useState('')
	const [password, setPassword] = useState('')
	const [twoFactorCode, setTwoFactorCode] = useState('')
	const [twoFactorToken, setTwoFactorToken] = useState<string | null>(null)
	const [twoFactorEmail, setTwoFactorEmail] = useState('')
	const [error, setError] = useState('')
	const { refreshUser } = useAuth()

	const resetLogin = () => {
		setTwoFactorCode('')
		setTwoFactorToken(null)
		setTwoFactorEmail('')
		setError('')
	}

	const handleClose = () => {
		resetLogin()
		onClose()
	}

	const handleLogin = async (e: React.FormEvent<HTMLFormElement>) => {
		e.preventDefault()
		setLoading(true)
		setError('')
		try {
			const response = await login({
				identifier: identifier.trim(),
				password,
			})
			if ("accessToken" in response) {
				await refreshUser()
				navigate("/home")
			} else {
				setTwoFactorToken(response.twoFactorToken)
				setTwoFactorEmail(response.user.email)
			}
		} catch (error) {
			setError(error instanceof Error ? error.message : t('2FA.login_failed'))
		}
		finally {
			setLoading(false)
		}
	}

	const handleTwoFactorVerification = async (e: React.FormEvent<HTMLFormElement>) => {
		e.preventDefault()
		if (!twoFactorToken) return

		setLoading(true)
		setError('')
		try {
			await verifyTwoFactor(twoFactorToken, twoFactorCode)
			await refreshUser()
			navigate("/home")
		} catch {
			setError(t('2FA.two_factor_invalid'))
			setTwoFactorCode('')
		} finally {
			setLoading(false)
		}
	}

	if (isOpen && twoFactorToken) {
		return (
			<div className="fixed inset-0 z-40 overflow-y-auto">
				<div className="min-h-dvh flex items-center justify-center p-4">
					<Card
						className="gap-1"
						titleKey="2FA.two_factor_title"
						isOpen={isOpen}
						onClose={handleClose}
					>
						<form
							className="w-full max-w-md mx-auto px-4 pt-0 pb-1 flex flex-col gap-5"
							onSubmit={handleTwoFactorVerification}
						>
							<p className="text-center text-info">
								{t('2FA.two_factor_sent', { email: maskEmail(twoFactorEmail) })}
							</p>
							<Input
								labelKey="2FA.two_factor_code"
								value={twoFactorCode}
								onChange={(e) => setTwoFactorCode(e.target.value.replace(/\D/g, '').slice(0, 6))}
								placeHolderKey="2FA.enter_two_factor_code"
								type="text"
							/>
							{error && <p className="text-center text-red-400" role="alert">{error}</p>}
							<div className="flex justify-center mt-5">
								<Button
									type="submit"
									variant="primary"
									className="w-2/3 sm:w-1/2"
									disabled={loading || twoFactorCode.length !== 6}
								>
									{loading ? (<Spinner size="sm" variant="light" />) : t('2FA.verify')}
								</Button>
							</div>
						</form>
					</Card>
				</div>
			</div>
		)
	}

	if (!isOpen)
		return null

	return (
		<div className="fixed inset-0 z-40 overflow-y-auto">
			<div className="min-h-dvh flex items-center justify-center p-4">
				<Card
					className="gap-1"
					titleKey="auth.login"
					isOpen={isOpen}
					onClose={handleClose}
					footer={<SocialLogin />}
				>
					<form 
						className="w-full max-w-md mx-auto px-4 pt-0 pb-1 flex flex-col gap-5"
						onSubmit={handleLogin}
					>

						<Input
							labelKey="auth.email_username"
							value={identifier}
							onChange={(e) => setIdentifier(e.target.value)}
							placeHolderKey="auth.enter_email_username"
							type="text"
						/>
						{error && <p className="text-center text-red-400" role="alert">{error}</p>}

						<Input
							labelKey="auth.password"
							value={password}
							onChange={(e) => setPassword(e.target.value)}
							placeHolderKey="auth.enter_password"
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
								: t('auth.login')}
							</Button>

							<Button
								type="button"
								variant="ghost"
								onClick={onRegister}
							>
								{t("auth.create_account")}
							</Button>
						</div>
					</form>
				</Card>
			</div>
		</div>
	)
}

export default LoginCard