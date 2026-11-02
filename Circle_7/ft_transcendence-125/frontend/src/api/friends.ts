import type {
	Friend,
	FriendRequest,
	UserSearchResult
} from "@/types/friendsTypes"
 
import { apiFetch } from "./fetch"
 
const FRIENDS_URL = "/api/user/friends"
 
 
export async function searchUsers(
	username: string,
): Promise<UserSearchResult[]> {
 
	const response = await apiFetch(
		`/api/user/users/search?username=${encodeURIComponent(username)}`,
		{
			method: "GET",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to search users")
 
	return response.json()
}
 
 
export async function getFriends(): Promise<Friend[]> {
 
	const response = await apiFetch(
		FRIENDS_URL,
		{
			method: "GET",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to fetch friends")
 
	return response.json()
}
 
export async function removeFriend(
	friendId: number,
): Promise<void> {
 
	const response = await apiFetch(
		`${FRIENDS_URL}/${friendId}`,
		{
			method: "DELETE",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to delete friend")
}
 
export async function getFriendRequests(): Promise<FriendRequest[]> {
 
	const response = await apiFetch(
		`${FRIENDS_URL}/requests`,
		{
			method: "GET",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to fetch friend requests")
 
	return response.json()
}
 
export async function acceptRequest(
	requestId: number,
): Promise<void> {
 
	const response = await apiFetch(
		`${FRIENDS_URL}/requests/${requestId}/accept`,
		{
			method: "PATCH",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to accept friend request")
}
 
export async function declineRequest(
	requestId: number,
): Promise<void> {
 
	const response = await apiFetch(
		`${FRIENDS_URL}/requests/${requestId}/decline`,
		{
			method: "PATCH",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to decline friend request")
}
 
export async function sendFriendRequest(
	targetId: number,
): Promise<void> {
 
	const response = await apiFetch(
		`${FRIENDS_URL}/request/${targetId}`,
		{
			method: "POST",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to send friend request")
}