import { useEffect, useRef, useState } from "react"
import { useTranslation } from "react-i18next"

import Avatar from "@/components/ui/Avatar"
import Button from "@/components/ui/Button"
import Spinner from "@/components/ui/Spinner"

import { useAuth } from "@/hooks/useAuth"
import { useChat } from "@/hooks/useChat"
import { usePresence } from "@/hooks/usePresence"


function ChatBubble(){

	const { t } = useTranslation()

	const { user } = useAuth()
	const {
		isOpen,
		activeConversation,
		conversations,
		messages,
		loading,
		error,
		toggleChat,
		closeChat,
		closeConversation,
		openConversation,
		sendMessage,
		refreshConversations,
		unreadByRoom,
	} = useChat()

	const [input, setInput] = useState("")
	const messagesEndRef = useRef<HTMLDivElement | null>(null)
	const totalUnread = Object.values(unreadByRoom).reduce(
		(total, count) => total + count, 0,)
	const {isOnline, fetchPresence} = usePresence()

	useEffect(() => {
		if (!isOpen)
			return
		void refreshConversations()
	}, [isOpen, refreshConversations])

	useEffect(() => {
		messagesEndRef.current?.scrollIntoView({
			behavior: "smooth",
		})
	}, [messages])

	useEffect(() => {
		if (!isOpen)
			return

		if (!activeConversation)
			return

		requestAnimationFrame(() => {
			messagesEndRef.current?.scrollIntoView({
				behavior: "auto",
			})
		})
	}, [
		isOpen,
		activeConversation,
	])

	useEffect(() => {
		setInput("")
	}, [activeConversation])

	const handleSubmit = (event: React.FormEvent) => {
		event.preventDefault()
		const message = input.trim()
		if (!message)
			return
		sendMessage(message)
		setInput("")
	}

	useEffect(() => {
		const friendIds = conversations
				.filter(
					(conversation) =>
						conversation.type === "private" &&
						conversation.friendId !== undefined
					)
				.map((conversation) => conversation.friendId!)
		if (friendIds.length === 0)
			return
		fetchPresence(friendIds)
	}, [conversations, fetchPresence])

	return (
	<>
		{isOpen && (
			<div className="fixed bottom-24 right-6 z-50 w-[360px] h-[500px] bg-black border-2 border-info rounded-2xl shadow-2xl flex flex-col overflow-hidden">
				<div className="h-16 shrink-0 border-b border-info/50 flex items-center justify-between px-4">
					<div className="flex items-center gap-3 min-w-0">
						{activeConversation && (
							<Button
								variant="ghost"
								onClick={closeConversation}
								className="w-8 h-8 p-0 text-info"
							>
								←
							</Button>
						)}

						<div className="min-w-0">
							<div className="flex items-center gap-2">
								<p className="font-micro-5 text-info text-3xl truncate">
									{activeConversation ? activeConversation.name : "Chat"}
								</p>

								{activeConversation?.type === "private" &&
									activeConversation.friendId !== undefined && (
										<span
											className={`w-2 h-2 shrink-0 rounded-full ${
												isOnline(activeConversation.friendId)
													? "bg-success"
													: "bg-error"
											}`}
										/>
									)}
							</div>

							{activeConversation && (
								<p className="font-micro-5 text-lg text-white/50">
									{activeConversation.type === "lobby"
										? "Lobby"
										: isOnline(activeConversation.friendId!)
											? t("status.online")
											: t("status.offline")}
								</p>
							)}
						</div>
					</div>

					<Button
						variant="ghost"
						onClick={closeChat}
						className="w-8 h-8 p-0 text-info"
					>
						×
					</Button>
				</div>

				{error && (
					<div className="px-4 py-2 bg-error/20 border-b border-error/50">
						<p className="font-micro-5 text-error text-lg">
							{error}
						</p>
					</div>
				)}

				{!activeConversation && (
					<div className="flex-1 overflow-y-auto p-3">
						{loading ? (
							<div className="h-full flex items-center justify-center">
								<Spinner size="sm" variant="light" />
							</div>
						) : conversations.length === 0 ? (
							<div className="h-full flex items-center justify-center">
								<p className="font-micro-5 text-info/60 text-2xl text-center">
									{t("chat.no_conv")}
								</p>
							</div>
						) : (
							<div className="flex flex-col gap-2">
								{conversations.map((conversation) => {
									const unread =
										unreadByRoom[conversation.room] ?? 0

									return (
										<button
											key={conversation.id}
											type="button"
											onClick={() =>
												openConversation(conversation)
											}
											className="w-full flex items-center gap-3 px-3 py-3 rounded-xl text-left border border-transparent hover:border-info/50 hover:bg-info/10 transition-colors"
										>
											{conversation.type === "lobby" ? (
												<div className="w-8 h-8 shrink-0 rounded-full bg-info/60 flex items-center justify-center font-micro-5 text-black text-2xl">
													#
												</div>
											) : (
												<Avatar
													pseudo={conversation.name}
													src={
														conversation.avatarUrl ??
														undefined
													}
													size="sm"
												/>
											)}

											<div className="min-w-0 flex-1">
												<div className="flex items-center gap-2">
													<p className="font-micro-5 text-info text-2xl truncate">
														{conversation.name}
													</p>

													{conversation.type === "private" &&
														conversation.friendId !== undefined && (
															<span
																className={`w-2 h-2 shrink-0 rounded-full ${
																	isOnline(conversation.friendId)
																		? "bg-success"
																		: "bg-error"
																}`}
															/>
														)}
												</div>

												<p className="font-micro-5 text-white/50 text-lg">
													{conversation.type === "lobby"
														? t("chat.lobby_chat")
														: t("chat.private_msg")}
												</p>
											</div>

											{unread > 0 && (
												<div className="min-w-6 h-6 px-1 rounded-full bg-error text-white flex items-center justify-center text-xs font-bold">
													{unread > 99
														? "99+"
														: unread}
												</div>
											)}
										</button>
									)
								})}
							</div>
						)}
					</div>
				)}

				{activeConversation && (
					<>
						<div className="flex-1 overflow-y-auto px-4 py-4">
							{messages.length === 0 ? (
								<div className="h-full flex items-center justify-center">
									<p className="font-micro-5 text-info/50 text-2xl">
										{t("chat.no_msg")}
									</p>
								</div>
							) : (
								<div className="flex flex-col gap-3">
									{messages.map((message, index) => {
										const isMine = message.userId === user?.id

										return (
											<div
												key={`${message.date}-${message.userId}-${index}`}
												className={`flex ${isMine ? "justify-end" : "justify-start"}`}
											>
												<div className={`max-w-[78%] ${isMine ? "text-right" : "text-left"}`}>
													{!isMine && (
														<p className="font-micro-5 text-info text-lg mb-1 px-1">
															{message.username}
														</p>
													)}

													<div
														className={`px-3 py-2 rounded-xl text-sm break-words ${
															isMine
																? "bg-info text-black"
																: "bg-white/10 text-white border border-info/30"
														}`}
													>
														{message.message}
													</div>

													<p className="text-[10px] text-white/30 mt-1 px-1">
														{new Date(message.date).toLocaleTimeString([], {
															hour: "2-digit",
															minute: "2-digit",
														})}
													</p>
												</div>
											</div>
										)
									})}

									<div ref={messagesEndRef} />
								</div>
							)}
						</div>

						<form onSubmit={handleSubmit} className="shrink-0 border-t border-info/50 p-3">
							<div className="flex items-center gap-2">
								<input
									type="text"
									value={input}
									onChange={(event) => setInput(event.target.value)}
									placeholder={t("chat.type_msg")}
									maxLength={500}
									className="flex-1 min-w-0 bg-black border border-info rounded-xl px-3 py-2 text-sm text-white placeholder:text-white/30 outline-none focus:bg-info/10"
								/>

								<Button
									type="submit"
									variant="info"
									disabled={input.trim().length === 0}
									className="w-10 h-10 p-0"
								>
									→
								</Button>
							</div>
						</form>
					</>
				)}
			</div>
		)}

		<div className="fixed bottom-6 right-6 z-50">
			<Button
				variant="info"
				onClick={toggleChat}
				className="h-12 px-5"
			>
				Chat
			</Button>

			{totalUnread > 0 && (
				<div className="absolute -top-2 -right-2 min-w-6 h-6 px-1 rounded-full bg-error text-white flex items-center justify-center text-xs font-bold">
					{totalUnread > 99
						? "99+"
						: totalUnread}
				</div>
			)}
		</div>
	</>
	)
}


export default ChatBubble