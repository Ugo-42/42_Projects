type SpinnerProps = {
    size: 'sm' | 'lg'
    variant: 'light' | 'dark'
    className?: string
}


function Spinner({ size, variant, className = '' }: SpinnerProps) {


    const sizes= {
        sm: { outer:'w-6 h-6', inner: 'size-4' },
        lg: { outer:'w-15 h-15', inner: 'size-10' },
    }


    const variants= {
        light: 'border-white',
        dark: 'border-black',
    }
    return (
        <div
            className={`${sizes[size].outer} inline-flex items-center justify-center } ${className}`}
            role="status"
            aria-label="loading"
        >
            <span className={`${sizes[size].inner} relative flex items-center justify-center`} aria-hidden="true" >
                <span className={`absolute inline-flex ${sizes[size].inner } rounded-full border-2 ${variants[variant]} animate-ping`}></span>
                <span className={`inline-flex ${sizes[size].inner } rounded-full border-4 ${variants[variant]}`}></span>
            </span>
            <span className="sr-only">Loading...</span>
        </div>
    )
}


export default Spinner