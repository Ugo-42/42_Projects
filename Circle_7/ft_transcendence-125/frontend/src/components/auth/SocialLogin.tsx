import Button from '../ui/Button'

import { useTranslation } from 'react-i18next'

function GoogleIcon() {
	return (
		<svg
			viewBox="0 0 24 24"
			className="w-8 h-8"
			aria-hidden="true"
		>
			<path
				fill="#4285F4"
				d="M21.35 12.27c0-.79-.07-1.55-.2-2.27H12v4.3h5.24a4.48 4.48 0 0 1-1.95 2.94v2.45h3.16c1.85-1.7 2.9-4.2 2.9-7.42z"
			/>
			<path
				fill="#34A853"
				d="M12 21.5c2.65 0 4.87-.88 6.49-2.39l-3.16-2.45c-.88.59-2 .94-3.33.94-2.56 0-4.73-1.73-5.51-4.06H3.22v2.53A9.8 9.8 0 0 0 12 21.5z"
			/>
			<path
				fill="#FBBC05"
				d="M6.49 13.54a5.9 5.9 0 0 1 0-3.08V7.93H3.22a9.5 9.5 0 0 0 0 8.14l3.27-2.53z"
			/>
			<path
				fill="#EA4335"
				d="M12 6.4c1.44 0 2.74.5 3.76 1.48l2.82-2.82C16.87 3.54 14.65 2.5 12 2.5a9.8 9.8 0 0 0-8.78 5.43l3.27 2.53C7.27 8.13 9.44 6.4 12 6.4z"
			/>
		</svg>
	)
}

function SocialLogin() {

	const { t } = useTranslation()

	return (
		<div className="flex flex-col items-center gap-1 w-full">

			<div className="flex items-center gap-3 w-full">

				<div className="h-px flex-1 bg-base-content/30" />

				<span className="font-micro-5 text-info text-xl">
					{t("or")}
				</span>
				<div className="h-px flex-1 bg-base-content/30" />
			</div>

			<span className="font-micro-5 text-info text-xl">
				{t("auth.signup_with")}
			</span>

			<Button
				type="button"
				onClick={() => { window.location.href = "/api/auth/google" }}
				variant="ghost"
				className="
					w-16 h-16
					!p-0
					rounded-full
					border
					border-base-content/60
					flex items-center justify-center
				"
			>
				<GoogleIcon />
			</Button>
		</div>
	)
}

export default SocialLogin