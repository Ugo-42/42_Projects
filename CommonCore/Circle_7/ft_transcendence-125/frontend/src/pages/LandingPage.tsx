import Button from '../components/ui/Button'
import Dropdown from '@/components/ui/Dropdown'

import PublicLayout from '../components/layouts/PublicLayout'

import LoginCard from '../components/auth/LoginCard'
import RegisterCard from '../components/auth/RegisterCard'

import { useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { useTranslation } from 'react-i18next'

function LandingPage() {

	const { t, i18n } = useTranslation()
	const navigate = useNavigate()

    const [language, setLanguage] = useState('dropdown.en')

	const languageOptions = [
		{ labelKey: "dropdown.en", onClick: () => {setLanguage('EN'); i18n.changeLanguage('en')} },
		{ labelKey: "dropdown.fr", onClick: () => {setLanguage('FR'); i18n.changeLanguage('fr')} },
		{ labelKey: "dropdown.es", onClick: () => {setLanguage('ES'); i18n.changeLanguage('es')} },
    ]

	const [loginOpen, setLoginOpen] = useState(false)
	const [registerOpen, setRegisterOpen] = useState(false)

	return (

		<PublicLayout>
		<div className="min-h-screen flex flex-col relative">
			<header className="fixed top-4 right-4 z-50">
				<Dropdown
					options={languageOptions}
					selectedKey={language}
					variant='info'
					align="down"
      			/>
			</header>
			<main className="flex-1 flex flex-col items-center justify-center">

				<div className="text-center">
					<h1 className="text-6xl md:text-[125px] lg:text-[200px] font-micro-5 text-primary">
						BOMBERMAN
					</h1>
				</div>

				<div className="flex gap-4 mt-8">

					<Button
						onClick={() => setLoginOpen(true)}
					>
						{t('auth.login')}
					</Button>

					<Button
						variant="secondary"
						onClick={() => setRegisterOpen(true)}
					>
						{t('auth.register')}
					</Button>

				</div>

			</main>

			<footer className="flex justify-center pb-6">
				<Button variant="ghost"
					onClick={() => navigate("/terms")}>
					{t('terms.terms_of_service')}
				</Button>
				<Button variant="ghost"
					onClick={() => navigate("/policy")}>
					{t('terms.privacy_policy')}
				</Button>
			</footer>

			<LoginCard
				isOpen={loginOpen}
				onClose={() => setLoginOpen(false)}
				onRegister={() => {
					setLoginOpen(false)
					setRegisterOpen(true)
				}}
			/>

			<RegisterCard
				isOpen={registerOpen}
				onClose={() => setRegisterOpen(false)}
				onLogin={() => {
					setRegisterOpen(false)
					setLoginOpen(true)
				}}
			/>
		</div>
	</PublicLayout>
	)
}

export default LandingPage