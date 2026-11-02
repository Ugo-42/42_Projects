import { useTranslation } from "react-i18next"

type InputProps = {
    value: string
    onChange: (e: React.ChangeEvent<HTMLInputElement>) => void
    labelKey: string
    placeHolderKey?: string
    type?: 'text' | 'email' | 'password'


}


function Input({ value, onChange, labelKey, placeHolderKey, type = 'text' }: InputProps) {
    
    const { t } = useTranslation()

    return (
        <div className="flex flex-col gap-1">
            <label className="text-lg text-info font-micro-5">
                {t(labelKey)}
            </label>
            <input
                placeholder={placeHolderKey ? t(placeHolderKey) : ''}
                value={value}
                onChange={onChange}
                type={type}
                className="border border-info w-full rounded-md px-3 py-2 text-white"
            />
        </div>
    )
}


export default Input