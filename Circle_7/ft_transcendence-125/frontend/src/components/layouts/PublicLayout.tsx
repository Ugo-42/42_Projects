type Props = {
	children: React.ReactNode;
};

function PublicLayout({ children }: Props) {
	return (
		<div className="min-h-screen bg-black flex items-center justify-center p-6">
			{children}
		</div>
	)
}

export default PublicLayout;