import { Injectable } from '@nestjs/common'
import { Socket } from 'socket.io'

@Injectable()
export class PresenceService {
	private onlineUsers =
		new Map<
			number,
			Map<
				string,
				Map<string, Socket>
			>
		>()

	private onlineListeners =
		new Set<
			(userId: number) => void
		>()

	private offlineListeners =
		new Set<
			(userId: number) => void
		>()

	onOnline(
		listener: (userId: number) => void,
	){
		this.onlineListeners.add(listener)
	}
	
	onOffline(
		listener: (userId: number) => void,
	){
		this.offlineListeners.add(listener)
	}

	addUser(
		userId: number,
		namespace: string,
		socket: Socket,
	){
		const wasOnline = this.isOnline(userId)
		let userSockets = this.onlineUsers.get(userId)

		if (!userSockets) {
			userSockets =
				new Map<
					string,
					Map<string, Socket>
				>()

			this.onlineUsers.set(
				userId,
				userSockets,
			)
		}

		let namespaceSockets =
			userSockets.get(namespace)

		if (!namespaceSockets) {
			namespaceSockets =
				new Map<string, Socket>()

			userSockets.set(
				namespace,
				namespaceSockets,
			)
		}

		namespaceSockets.set(
			socket.id,
			socket,
		)

		if (!wasOnline)
			for (const listener of this.onlineListeners)
				listener(userId)
	}

	removeUser(
		userId: number,
		namespace: string,
		socket: Socket,
	){
		const userSockets =
			this.onlineUsers.get(userId)

		if (!userSockets)
			return

		const namespaceSockets =
			userSockets.get(namespace)

		if (!namespaceSockets)
			return

		namespaceSockets.delete(socket.id)

		if (namespaceSockets.size === 0)
			userSockets.delete(namespace)

		if (userSockets.size > 0)
			return

		this.onlineUsers.delete(userId)

		for (const listener of this.offlineListeners)
			listener(userId)
	}

	getUserSockets(
		userId: number,
		namespace: string,
	){
		const userSockets =
			this.onlineUsers.get(userId)

		if (!userSockets)
			return []

		const namespaceSockets =
			userSockets.get(namespace)

		if (!namespaceSockets)
			return []

		return Array.from(
			namespaceSockets.values(),
		)
	}

	isOnline(
		userId: number,
	){
		const userSockets =
			this.onlineUsers.get(userId)

		if (!userSockets)
			return false

		for (const sockets of userSockets.values()) {
			if (sockets.size > 0)
				return true
		}

		return false
	}

	getOnlineCount(){
		return this.onlineUsers.size
	}
}