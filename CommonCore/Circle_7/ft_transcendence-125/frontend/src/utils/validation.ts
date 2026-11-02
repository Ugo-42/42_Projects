import type { RegisterRequest } from "@/types/authTypes"
import type { ProfileEditRequest } from "@/types/profileTypes"

function containsNonPrintable(value: string): boolean {
	return /\p{C}|\p{Extended_Pictographic}/u.test(value)
}


export function validateRegister(
	data: RegisterRequest,
	confirmPassword: string,
): string | null {

	if (containsNonPrintable(data.username))
		return "Username contains invalid characters."

	if (containsNonPrintable(data.email))
		return "Email contains invalid characters."

	if (containsNonPrintable(data.password))
		return "Password contains invalid characters."

	if (containsNonPrintable(confirmPassword))
		return "Password confirmation contains invalid characters."

	if (!data.username.trim())
		return "Username is required."

	if (data.username.length < 3 || data.username.length > 12)
		return "Username must contain at least 3 characters and less than 12 characters."

	if (!data.email.trim())
		return "Email is required."

	const emailRegex =
		/^[^\s@]+@[^\s@]+\.[^\s@]+$/

	if (!emailRegex.test(data.email))
		return "Invalid email address."

	if (!data.password)
		return "Password is required."

	if (data.password.length < 8)
		return "Password must contain at least 8 characters."

	if (data.password.length > 64)
		return "Password can't contain more than 64 characters."

	if (!/[A-Z]/.test(data.password))
		return "Password must contain an uppercase letter."

	if (!/[a-z]/.test(data.password))
		return "Password must contain a lowercase letter."

	if (!/[0-9]/.test(data.password))
		return "Password must contain a number."

	if (data.password !== confirmPassword)
		return "Passwords do not match."

	return null
}

export function validateProfileEdit(
	data: ProfileEditRequest,
	confirmPassword: string,
): string | null {

	if (data.username) {
		if (containsNonPrintable(data.username))
			return "Username contains invalid characters."
		
		if (data.username.length < 3 || data.username.length > 12)
			return "Username must contain at least 3 characters and less than 12 characters."
	}

	if (data.email) {
		if (containsNonPrintable(data.email))
			return "Email contains invalid characters."

		const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/

		if (!emailRegex.test(data.email))
			return "Invalid email address."
	}

	const wantsPasswordChange =
		Boolean(data.currentPassword) ||
		Boolean(data.newPassword) ||
		Boolean(confirmPassword)

	if (wantsPasswordChange) {
		if (!data.currentPassword)
			return "Current password is required."

		if (!data.newPassword)
			return "New password is required."

		if (!confirmPassword)
			return "Password confirmation is required."

		if (containsNonPrintable(data.currentPassword))
			return "Current password contains invalid characters."

		if (containsNonPrintable(data.newPassword))
			return "New password contains invalid characters."

		if (containsNonPrintable(confirmPassword))
			return "Password confirmation contains invalid characters."

		if (data.newPassword.length < 8)
			return "Password must contain at least 8 characters."

		if (!/[A-Z]/.test(data.newPassword))
			return "Password must contain an uppercase letter."

		if (!/[a-z]/.test(data.newPassword))
			return "Password must contain a lowercase letter."

		if (!/[0-9]/.test(data.newPassword))
			return "Password must contain a number."

		if (data.newPassword !== confirmPassword)
			return "Passwords do not match."
	}

	return null
}