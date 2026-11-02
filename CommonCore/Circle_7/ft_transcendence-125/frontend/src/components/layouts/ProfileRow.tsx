type ProfileRowProps = {
    label: string
    value: React.ReactNode
}

function ProfileRow({ label, value }: ProfileRowProps) {
    return (
        <div className="flex justify-between border-b border-white/20 text-info pb-2">
            <span>{label}</span>
            <span>{value}</span>
        </div>
    )
}

export default ProfileRow