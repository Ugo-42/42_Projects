import { useEffect } from "react"
import Button from '@/components/ui/Button'
import { useTranslation } from "react-i18next"


type ToastProps = {
    labelKey: string
    variant: 'success' | 'error' | 'warning' | 'info'
    timing?: number
    onClose: () => void
    className?: string
}


function Toast({ labelKey, variant, timing = 3000, onClose, className='' }: ToastProps) {

    const { t } = useTranslation()

  const variants = {
    success:   'bg-success/80 text-white hover:bg-success',
    error:     'bg-error/70 text-white hover:bg-error',
    warning:   'bg-warning/80 text-black hover:bg-warning',
    info:      'bg-info/80 text-white hover:bg-info',
  }


    useEffect(() => {
        const timer = setTimeout(() => {
            onClose()
        }, timing)
        return () => clearTimeout(timer)
    }, [timing, onClose])


    return (
        <div className={ `fixed top-5 right-5 px-2 py-1 rounded-lg shadow-xl font-micro-5 ${variants[variant]} ${className}` }>
            <Button type="button" variant="ghost" onClick={onClose} className="absolute top-0 right-0 leading-none">
                x
            </Button>
            <p className="pr-6">{t(labelKey)}</p>
        </div>
    )
}
export default Toast