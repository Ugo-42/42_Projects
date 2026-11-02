import { useTranslation } from "react-i18next"

type BadgeProps = {
    labelKey: string
    variant: 'primary' | 'secondary' | 'success' | 'error' | 'warning' | 'info'
    className?: string
}


function Badge({ labelKey, variant='primary', className='' }: BadgeProps) {

    const { t } = useTranslation()

    const variants = {
        primary: 'bg-primary/90',
        secondary: 'bg-secondary/90',
        success: 'bg-success/90',
        error: 'bg-error/90',
        warning: 'bg-warning/90',
        info: 'bg-info/90',
    }
    return (
        <span className={`px-2 rounded-lg text-xs md:text-sm font-micro-5 text-black ${variants[variant]} ${className}`} >
            {t(labelKey)}
        </span>
    )
}


export default Badge