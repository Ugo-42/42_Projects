type AvatarProps = {
    pseudo: string
    src?: string | undefined
    size?: 'sm' | 'md' | 'lg'
    className?: string
}


function Avatar({ pseudo, src, size = 'md', className }: AvatarProps) {


    const sizes = {
        sm: 'w-8 h-8 text-lg',
        md: 'w-16 h-16 text-3xl',
        lg: 'w-24 h-24 md:w-36 md:h-36 text-6xl',
    }


    const initial = pseudo[0].toUpperCase()




    return (
        <div className={`${sizes[size]} rounded-full flex items-center justify-center bg-info/60 font-micro-5 overflow-hidden ${className}`}>
            {src? (
                <img src={src} alt={pseudo} className="w-full h-full rounded-full object-cover" />
            ) : (
                <span>{initial}</span>
            )}
        </div>
    )
}


export default Avatar