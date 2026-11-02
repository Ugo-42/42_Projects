import * as profileApi from "../api/profile"

import type {
	ProfileEditRequest,
} from "../types/profileTypes"


export async function getMyProfile() {
	return profileApi.getMyProfile()
}


export async function updateProfile(
	data: ProfileEditRequest,
) {
	return profileApi.updateProfile(data)
}

export async function uploadAvatar(file: File) {
	const profile = await profileApi.uploadAvatar(file)
	const storedUser = localStorage.getItem("user")
	if (storedUser) {
		localStorage.setItem(
			"user",
			JSON.stringify({ ...JSON.parse(storedUser), avatarUrl: profile.avatarUrl }),
		)
	}
	return profile
}


export async function updateAccount(
	data: ProfileEditRequest,
) {
	const updatedUser =
		await profileApi.updateAccount(data)

	localStorage.setItem(
		"user",
		JSON.stringify(updatedUser),
	)

	return updatedUser
}

export async function getProfileById(
	userId: number,
) {
	return profileApi.getProfileById(userId)
}

export async function deleteAccount() {
	await profileApi.deleteAccount()
	localStorage.removeItem("user")
	localStorage.removeItem("token")
}