import Button from "./Button"

type ModalProps = {
	children: React.ReactNode
	footer: React.ReactNode
	isOpen: boolean
	onClose: () => void
	className?: string
}

function Modal({ children, footer, isOpen = false, onClose, className = '' }: ModalProps) {
	
	if (!isOpen)
		return null

	const base = 'bg-black/50 bg-blend-overlay'

	return (
		<div className={ `fixed inset-0 ${base} flex items-center justify-center z-50 ${className}` }>
			<div className={ `bg-black border-2 border-info rounded-lg font-micro-5 text-white text-2xl p-6 relative` }>
            <Button type="button" variant="ghost" onClick={onClose} className="absolute top-0 right-0">
                x
            </Button>
				{children}
				{footer && 
				<div className="flex justify-center gap-3 p-1 pt-4"> {footer} </div>}
			</div>
		</div>
	)
}

export default Modal