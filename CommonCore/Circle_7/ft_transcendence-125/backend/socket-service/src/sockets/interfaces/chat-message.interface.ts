export interface ChatMessage {
	room: string;
	userId: number;
	username: string;
	message: string;
	date: Date;
}