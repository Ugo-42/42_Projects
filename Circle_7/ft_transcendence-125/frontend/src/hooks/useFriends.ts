import {
	useEffect,
	useState,
} from "react"

import {
	getFriends,
	removeFriend,
	getFriendRequests,
	acceptRequest,
	declineRequest,
	sendFriendRequest,
	searchUsers,
} from "@/services/friendsService"

import {
	connectSocket, getAppSocket,
} from "@/services/socketService"

import type {
	Friend,
	FriendRequest,
	UserSearchResult,
} from "@/types/friendsTypes"


export function useFriends() {

	const [friends, setFriends] = useState<Friend[]>([])
	const [requests, setRequests] = useState<FriendRequest[]>([])
	const [loading, setLoading] = useState(true)
	const [selectedFriendId, setSelectedFriendId] = useState<number | null>(null)
	const [showRemovedToast, setShowRemovedToast] = useState(false)
	const [showAcceptedToast, setShowAcceptedToast] = useState(false)
	const [showDeclinedToast, setShowDeclinedToast] = useState(false)
	const [showInviteToast, setShowInviteToast] = useState(false)
	const [showInviteErrorToast, setShowInviteErrorToast] = useState(false)
	const [activeTab, setActiveTab] = useState<"list" | "requests">("list")
	const [showAddFriendModal, setShowAddFriendModal] = useState(false)
	const [searchUsername, setSearchUsername] = useState("")
	const [searchResults, setSearchResults] = useState<UserSearchResult[]>([])
	const [searching, setSearching] = useState(false)



	const handleRemoveFriend = async (
		friendId: number,
	) => {
		try {
			await removeFriend(friendId)
			setFriends((prev) =>
				prev.filter(
					(friend) =>
						friend.id !== friendId,
				),
			)
			setShowRemovedToast(true)
		} catch (error) {
			console.error(
				"Error removing friend:",
				error,
			)
		}
	}



	const handleSearchUsers = async () => {
		const value =
			searchUsername.trim()
		if (!value) {
			setSearchResults([])
			return
		}
		try {
			setSearching(true)
			const results =
				await searchUsers(value)
			setSearchResults(results)
		} catch (error) {
			console.error(
				"Error searching users:",
				error,
			)
			setSearchResults([])
		} finally {
			setSearching(false)
		}
	}


	const handleAcceptRequest = async (
		requestId: number,
	) => {
		try {
			await acceptRequest(requestId)
			const accepted =
				requests.find(
					(request) =>
						request.id === requestId,
				)
			setRequests((prev) =>
				prev.filter(
					(request) =>
						request.id !== requestId,
				),
			)
			if (accepted) {
				setFriends((prev) => [
					...prev,
					{
						id: accepted.sender.id,
						username:
							accepted.sender.username,
						avatarUrl:
							accepted.sender.avatarUrl,
					},
				])
			}
			setShowAcceptedToast(true)
		} catch (error) {
			console.error(
				"Error accepting friend request",
				error,
			)
		}
	}


	const handleDeclineRequest = async (
		requestId: number,
	) => {
		try {
			await declineRequest(requestId)
			setRequests((prev) =>
				prev.filter(
					(request) =>
						request.id !== requestId,
				),
			)
			setShowDeclinedToast(true)
		} catch (error) {
			console.error(
				"Error declining friend request",
				error,
			)
		}
	}


	const handleSendRequest = async (
		targetId: number,
	) => {
		try {
			await sendFriendRequest(targetId)
			setShowInviteToast(true)
		} catch (error) {
			console.error(
				"Error sending friend invite",
				error,
			)
			setShowInviteErrorToast(true)
		}
	}


	useEffect(() => {
		let friendsDone = false
		let requestsDone = false
		function checkAllDone() {
			if (
				friendsDone &&
				requestsDone
			) {
				setLoading(false)
			}
		}


		async function fetchFriends() {
			try {
				const response =
					await getFriends()
				setFriends(response)
			} catch (error) {
				console.error(
					"Error fetching friends:",
					error,
				)
			} finally {
				friendsDone = true
				checkAllDone()
			}
		}


		async function fetchRequests() {
			try {
				const response =
					await getFriendRequests()
				setRequests(response)
			} catch (error) {
				console.error(
					"Error fetching requests:",
					error,
				)
			} finally {
				requestsDone = true
				checkAllDone()
			}
		}
		void fetchFriends()
		void fetchRequests()
	}, [])



	useEffect(() => {
		connectSocket()
		const socket =
			getAppSocket()
		if (!socket)
			return

		const handleFriendRequest =
			async () => {
				console.log(
					"[FRIENDS SOCKET] friend:request",
				)
				try {
					const response =
						await getFriendRequests()
					setRequests(response)
				} catch (error) {
					console.error(
						"Error refreshing friend requests:",
						error,
					)
				}
			}

		const handleFriendAccepted =
			async () => {
				console.log(
					"[FRIENDS SOCKET] friend:accepted",
				)
				try {
					const response =
						await getFriends()
					setFriends(response)
				} catch (error) {
					console.error(
						"Error refreshing friends:",
						error,
					)
				}
			}

		const handleFriendRemoved =
			async () => {
				console.log(
					"[FRIENDS SOCKET] friend:removed",
				)
				try {
					const response =
						await getFriends()

					setFriends(response)
				} catch (error) {
					console.error(
						"Error refreshing friends:",
						error,
					)
				}
			}

		socket.on("friend:request",handleFriendRequest,)
		socket.on("friend:accepted",handleFriendAccepted,)
		socket.on("friend:removed",handleFriendRemoved,)

		return () => {
			socket.off("friend:request",handleFriendRequest,)
			socket.off("friend:accepted",handleFriendAccepted,)
			socket.off("friend:removed",handleFriendRemoved,)
		}
	}, [])



	return {
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
	}
}