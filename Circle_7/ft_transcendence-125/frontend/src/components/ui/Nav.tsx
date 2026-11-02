import Button from './Button'
import { useTranslation } from 'react-i18next'

type NavItem = {
	labelKey: string
	onClick: () => void
}

type NavProps = {
	items: NavItem[]
	className?: string
	isOpen: boolean
	onToggle: () => void
}

function Nav({ items, className = '', isOpen, onToggle }: NavProps) {

	const { t } = useTranslation()

	return (
		<div className={className}>
			<Button
				variant='info'
				onClick={onToggle}
				className="fixed top-4 left-4 z-50 text-3xl"
			>
				MENU
			</Button>

			{isOpen && (
				<div className="fixed top-16 left-4 bg-white rounded-lg p-4 flex flex-col gap-2 z-50">
					{items.map((item) => (
						<button
							key={item.labelKey}
							onClick={item.onClick}
							className="text-black text-left text-xl font-micro-5 hover:bg-info/70 rounded-lg px-2"
						>
							{t(item.labelKey)}
						</button>
					))}
				</div>
			)}
		</div>
	)
}

export default Nav