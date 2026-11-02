import type {
	Profile,
	ProfilePrivate,
	ProfileEditRequest,
} from "@/types/profileTypes"
 
import { apiFetch } from "./fetch"
 
const PROFILE_URL = "/api/user/profile"
 
export async function getMyProfile(): Promise<ProfilePrivate> {
 
	const response = await apiFetch(
		`${PROFILE_URL}/me`,
		{
			method: "GET",
		},
	)
 
	if (!response.ok) {
		throw new Error("Failed to fetch profile")
	}
 
	return response.json()
}
 
 
export async function updateProfile(
	data: ProfileEditRequest,
): Promise<Profile> {
 
	const response = await apiFetch(
		`${PROFILE_URL}/me`,
		{
			method: "PATCH",
			headers: {
				"Content-Type": "application/json",
			},
			body: JSON.stringify(data),
		},
	)
 
	if (!response.ok) {
		throw new Error("Profile update failed")
	}
 
	return response.json()
}
 
export async function uploadAvatar(file: File): Promise<Profile> {
	const formData = new FormData()
	formData.append("file", file)
 
	const response = await apiFetch(
		`${PROFILE_URL}/me/avatar`,
		{
			method: "PATCH",
			body: formData,
		},
	)
 
	if (!response.ok) {
		throw new Error("Avatar upload failed")
	}
 
	return response.json()
}
 
export async function updateAccount(
	data: ProfileEditRequest,
) {
	const response = await apiFetch(
		"/api/user/users/me",
		{
			method: "PATCH",
			headers: {
				"Content-Type": "application/json",
			},
			body: JSON.stringify({
				username: data.username,
				email: data.email,
				currentPassword: data.currentPassword,
				newPassword: data.newPassword,
			}),
		},
	)
 
	if (!response.ok) {
		const error = await response.json().catch(() => null)
 
		throw new Error(
			error?.message || "Account update failed",
		)
	}
 
	return response.json()
}

export async function getProfileById(
	userId: number,
): Promise<Profile> {
 
	const response = await fetch(
		`${PROFILE_URL}/${userId}`,
		{
			method: "GET",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to fetch profile")
 
	return response.json()
}
 
export async function deleteAccount(): Promise<void> {
 
	const response = await apiFetch(
		`/api/user/users/me`,
		{
			method: "DELETE",
		},
	)
 
	if (!response.ok)
		throw new Error("Failed to delete account")
 
	return response.json()
}