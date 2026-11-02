import * as friendsApi from "@/api/friends"

export async function searchUsers(
	username: string,
) {
	return friendsApi.searchUsers(username)
}


export async function getFriends() {
	return friendsApi.getFriends()
}

export async function removeFriend(
	friendId: number,
) {
	return friendsApi.removeFriend(friendId)
}

export async function getFriendRequests() {
	return friendsApi.getFriendRequests()
}

export async function acceptRequest(
	requestId: number,
) {
	return friendsApi.acceptRequest(requestId)
}

export async function declineRequest(
	requestId: number,
) {
	return friendsApi.declineRequest(requestId)
}

export async function sendFriendRequest(
	targetId: number,
) {
	return friendsApi.sendFriendRequest(targetId)
}