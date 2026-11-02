import Button from "./Button"

import { useTranslation } from "react-i18next"


type CardProps = {
    children: React.ReactNode
    titleKey: string
    isOpen: boolean
    onClose: () => void
    footer?: React.ReactNode
    className?: string
}


function Card({children, titleKey, footer, isOpen = true, onClose, className = ''}:CardProps) {

    const { t } = useTranslation()

    if (!isOpen)
        return null
   
    return (
        <div className="relative p-8 rounded-2xl w-[90vw] md:w-1/3 bg-black border-2 border-info border-solid ${className}">
            <Button type="button" variant="ghost" onClick={onClose} className="absolute right-4 top-2 font-micro-5">
                x
            </Button>
            {titleKey && <h2 className="text-4xl md:text-5xl text-center font-micro-5 text-info mb-6">{t(titleKey)}</h2>}
            {children}
            {footer && <div className="mt-6 border-t border-info pt-6 flex justify-center">{footer}</div>}
            {className}
        </div>
    )
}


export default Card