type ButtonProps = {
  children: React.ReactNode
  variant?: 'primary' | 'secondary' | 'success'| 'error' | 'warning' | 'info' | 'ghost'
  onClick?: () => void
  disabled?: boolean
  type?: 'button' | 'submit'
  className?: string
}


function Button({
  children,
  variant = 'primary',
  onClick,
  disabled = false,
  type = 'button',
  className = ''
}: ButtonProps) {
  const base = 'font-medium rounded-lg duration-200'


  const variants = {
    primary:   'bg-primary/80 text-white hover:bg-primary',
    secondary: 'bg-secondary/80 text-black hover:bg-secondary',
    success:   'bg-success/80 text-white hover:bg-success',
    error:     'bg-error/80 text-white hover:bg-error',
    warning:   'bg-warning/80 text-black hover:bg-warning',
    info:      'bg-info/80 text-white hover:bg-info',
    ghost:     'bg-transparent text-white',
  }


  return (
    <button
      type={type}
      onClick={onClick}
      disabled={disabled}
      className={`font-micro-5 text-xl ${base} ${variants[variant]} px-3 py-1 rounded-xl flex items-center justify-center ${disabled ? 'opacity-90 cursor-not-allowed' : ''} ${className}`}
    >
      {children}
    </button>
  )
}


export default Button