import { useState, useRef } from "react";
import { useTranslation } from "react-i18next";

type DropdownOption = {
	labelKey: string
	onClick: () => void
}

type DropdownProps = {
	options: DropdownOption[]
	selectedKey: string;
	variant?: 'primary' | 'secondary' | 'info' | 'success' | 'warning' | 'error' | 'ghost'
	align?: 'right' | 'down'
	className?: string;
}

function Dropdown({ options, selectedKey, variant='primary', align='down', className = '' }: DropdownProps) {

	const { t } = useTranslation()
	const [showDropdown, setShowDropdown] = useState(false)
	const [menuPosition, setMenuPosition] = useState<{ top: number; left: number } | null>(null)
	const triggerRef = useRef<HTMLButtonElement>(null)

	const variants = {
		primary: 'bg-primary/80 text-white hover:bg-primary',
		secondary: 'bg-secondary/80 text-black hover:bg-secondary',
		info: 'bg-info/80 text-white hover:bg-info',
		success: 'bg-success/80 text-white hover:bg-success',
		warning: 'bg-warning/80 text-black hover:bg-warning',
		error: 'bg-error/80 text-white hover:bg-error',
		ghost: 'bg-transparent text-white',
	}

	const hoverVariants = {
		primary: 'hover:bg-primary/70',
		secondary: 'hover:bg-secondary/70',
		info: 'hover:bg-info/70',
		success: 'hover:bg-success/70',
		warning: 'hover:bg-warning/70',
		error: 'hover:bg-error/70',
		ghost: 'hover:bg-info/70'
	}

	const selectedVariants = {
		primary: 'bg-primary/70',
		secondary: 'bg-secondary/70',
		info: 'bg-info/70',
		success: 'bg-success/70',
		warning: 'bg-warning/70',
		error: 'bg-error/70',
		ghost: 'bg-transparent'
	}

	function handleToggle() {
		if (!showDropdown && triggerRef.current) {
			const rect = triggerRef.current.getBoundingClientRect()
			setMenuPosition(
				align === 'right'
					? { top: rect.top, left: rect.right + 4 }
					: { top: rect.bottom + 4, left: rect.left }
			)
		}
		setShowDropdown(!showDropdown)
	}

	return (
		<div className={`inline-block ${className}`}>
			<button
				ref={triggerRef}
				onClick={handleToggle}
				className={variants[variant] + ' font-micro-5 text-lg px-2 py-1 rounded-lg flex items-center justify-between w-full'}
			>
				{t(selectedKey ? selectedKey : '')}
			</button>
			{showDropdown && menuPosition && (
				<div
					style={{ position: 'fixed', top: menuPosition.top, left: menuPosition.left }}
					className="bg-white text-black rounded-lg px-2 py-1 whitespace-nowrap w-max z-50"
				>
					{options.map((option, index) => (
						<button
							key={index}
							onClick={() => {
								setShowDropdown(false);
								option.onClick();
							}}
							className={t(option.labelKey) === t(selectedKey)
								? `block w-full font-micro-5 text-sm px-2 py-1 mt-1 ${selectedVariants[variant]} rounded-lg`
								: `block w-full font-micro-5 text-sm px-2 py-1 mt-1 ${hoverVariants[variant]} rounded-lg`}
						>
							{t(option.labelKey)}
						</button>
					))}
				</div>
			)}
		</div>
	)
}

export default Dropdown