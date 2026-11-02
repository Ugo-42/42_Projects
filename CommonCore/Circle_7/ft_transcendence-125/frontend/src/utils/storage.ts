import type { User } from "@/types/authTypes"

export function getUser(): User | null {

    const data = localStorage.getItem("user")

    if (!data)
        return null

    return JSON.parse(data)
}