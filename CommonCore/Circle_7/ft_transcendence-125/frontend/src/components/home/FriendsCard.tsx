import Card from "../ui/Card"
import Button from "../ui/Button"
import Avatar from "../ui/Avatar"
import Badge from "../ui/Badge"
import Spinner from "../ui/Spinner"
import Dropdown from "../ui/Dropdown"
import Input from "../ui/Input"
import Toast from "../ui/Toast"

import ProfileFriendsCard from "./ProfileFriendsCard"

import {useTranslation} from "react-i18next"
import {useEffect} from "react"
import {useFriends} from "@/hooks/useFriends"
import {usePresence} from "@/hooks/usePresence"

type FriendsCardProps = {
	isOpen: boolean
	onClose: () => void
}

function FriendsCard({ isOpen, onClose }: FriendsCardProps) {

	const { t } = useTranslation()
	const {isOnline,fetchPresence} = usePresence()

	const {
		friends,
		requests,
		loading,

		selectedFriendId,
		setSelectedFriendId,

		activeTab,
		setActiveTab,

		showAddFriendModal,
		setShowAddFriendModal,

		searchUsername,
		setSearchUsername,

		searchResults,
		setSearchResults,

		searching,

		showRemovedToast,
		setShowRemovedToast,

		showAcceptedToast,
		setShowAcceptedToast,

		showDeclinedToast,
		setShowDeclinedToast,

		showInviteToast,
		setShowInviteToast,

		showInviteErrorToast,
		setShowInviteErrorToast,

		handleRemoveFriend,
		handleSearchUsers,
		handleAcceptRequest,
		handleDeclineRequest,
		handleSendRequest,
	} = useFriends()

	useEffect(() => {
		if (friends.length === 0)
			return
		fetchPresence(friends.map(
				(friend) => friend.id),
		)
	}, [friends,fetchPresence])

	if (!isOpen)
		return null

	if (loading) {
		return (
			<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
				<Spinner size="sm" variant="light" />
			</div>
		)
	}

	return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Card
				titleKey="nav.friends"
				isOpen={isOpen}
				onClose={onClose}
				footer={
					<div className="flex items-center gap-4">
						<Button
							variant="warning"
							onClick={() => setShowAddFriendModal(true)}
						>
							{t("button.add")}
						</Button>
						<Button
							variant="primary"
							onClick={onClose}
						>
							{t("button.close")}
						</Button>
					</div>
				}>

				<div className="flex flex-col items-center gap-3">

					<div className="flex items-center gap-2 py-2 px-10">
						<Button
							variant={activeTab === "list" ? "secondary" : "primary"}
							onClick={() => setActiveTab("list")}>
							{t("friends.list")}
						</Button>
						<Button
							variant={activeTab === "requests" ? "secondary" : "primary"}
							onClick={() => setActiveTab("requests")}>
							{t("friends.requests")}
						</Button>
					</div>

					<div className="w-full mt-5 space-y-5">
						{activeTab === "list" && (
							<ul className="max-h-64 scrollbar-thin scrollbar-thumb-info scrollbar-track-transparent overflow-y-auto">
								{friends.length === 0 ? (
									<p>No friends found.</p>
								) : (
									friends.map((friend) => (
										<li className="flex items-center justify-between py-2"
											key={friend.id}>
											<div className="flex items-center gap-2">
												<Avatar pseudo={friend.username} size="sm" src={friend.avatarUrl ?? undefined} />
												<p className="text-2xl font-micro-5 text-info flex-col">
													{friend.username}
												</p>
											</div>
											<div className="flex items-center">
												<Badge
													labelKey={isOnline(friend.id) ? "status.online" : "status.offline"}
													variant={isOnline(friend.id) ? "success" : "error"}
												/>
												<Dropdown
													selectedKey="⋮"
													variant="ghost"
													options={[
														{
															labelKey: "friends.view",
															onClick: () => setSelectedFriendId(friend.id),
														},
														{
															labelKey: "friends.remove",
															onClick: () => handleRemoveFriend(friend.id),
														},
													]}
													align="right"
												/>
											</div>
										</li>
									))
								)}
							</ul>
						)}

						{activeTab === "requests" && (
							<ul className="max-h-64 overflow-y-auto">
								{requests.length === 0 ? (
									<p>No requests found.</p>
								) : (
									requests.map((request) => (
										<li className="flex items-center justify-between py-2"
											key={request.id}>
											<div className="flex items-center gap-2">
												<Avatar pseudo={request.sender.username} size="sm" src={request.sender.avatarUrl ?? undefined} />
												<p className="text-2xl font-micro-5 text-info flex-col">
													{request.sender.username}
												</p>
											</div>
											<div className="flex items-center">
												<Dropdown
													selectedKey="⋮"
													variant="ghost"
													options={[
														{
															labelKey: "friends.accept",
															onClick: () => handleAcceptRequest(request.id),
														},
														{
															labelKey: "friends.decline",
															onClick: () => handleDeclineRequest(request.id),
														},
													]}
													align="right"
												/>
											</div>
										</li>
									))
								)}
							</ul>
						)}
					</div>
				</div>
			</Card>

			{selectedFriendId !== null && (
				<ProfileFriendsCard
					userId={selectedFriendId}
					isOpen={true}
					onClose={() => setSelectedFriendId(null)}
				/>
			)}

			{showAddFriendModal && (
				<div className="fixed inset-0 flex items-center justify-center z-50">
					<Card
						titleKey="button.add"
						isOpen={true}
						onClose={() => {
							setShowAddFriendModal(false)
							setSearchUsername("")
							setSearchResults([])
						}}
					>
						<div className="flex flex-col items-center justify-center gap-2">
							<Input
								labelKey=""
								placeHolderKey="friends.enter_id"
								type="text"
								value={searchUsername}
								onChange={(e) => setSearchUsername(e.target.value)}
							/>
							<Button
								variant="primary"
								onClick={() => {handleSearchUsers()}}
							>
								{t("button.search")}
							</Button>
							{searching && (
								<Spinner
									size="sm"
									variant="light"
								/>
							)}

							{!searching && searchResults.length > 0 && (
								<ul className="w-full max-h-48 overflow-y-auto">
									{searchResults.map((user) => (
										<li
											key={user.id}
											className="flex items-center justify-between py-2 gap-4"
										>
											<div className="flex items-center gap-2">
												<Avatar
													pseudo={user.username}
													size="sm"
													src={user.avatarUrl ?? undefined}
												/>

												<p className="text-xl font-micro-5 text-info">
													{user.username}
												</p>
											</div>

											<Button
												variant="success"
												onClick={async () => {
													await handleSendRequest(user.id)
													setShowAddFriendModal(false)
													setSearchUsername("")
													setSearchResults([])
												}}
											>
												{t("button.add")}
											</Button>
										</li>
									))}
								</ul>
							)}
						</div>
					</Card>
				</div>
			)}

			{showRemovedToast && (
				<Toast
					labelKey="toast.friends.removed"
					variant="success"
					onClose={() => setShowRemovedToast(false)}
				/>
			)}
			{showAcceptedToast && (
				<Toast
					labelKey="toast.requests.accepted"
					variant="success"
					onClose={() => setShowAcceptedToast(false)}
				/>
			)}
			{showDeclinedToast && (
				<Toast
					labelKey="toast.requests.declined"
					variant="success"
					onClose={() => setShowDeclinedToast(false)}
				/>
			)}
			{showInviteToast && (
				<Toast
					labelKey="toast.invites.success"
					variant="success"
					onClose={() => setShowInviteToast(false)}
				/>
			)}
			{showInviteErrorToast && (
				<Toast
					labelKey="toast.invites.fail"
					variant="error"
					onClose={() => setShowInviteErrorToast(false)}
				/>
			)}
		</div>
	)
}

export default FriendsCard