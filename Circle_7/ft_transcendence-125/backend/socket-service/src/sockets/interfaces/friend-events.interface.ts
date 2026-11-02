export interface FriendRequestEvent {
	id: number;
	sender: {
		id: number;
		username: string;
		avatarUrl: string | null;
	};
}

export interface FriendAcceptedEvent {
	id: number;
	username: string;
	avatarUrl: string | null;
}

export interface FriendRemovedEvent {
	userId: number;
}