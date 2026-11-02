# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    database.sql                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfaechti <benjamin.faechtig@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/29 13:45:40 by bfaechti          #+#    #+#              #
#    Updated: 2026/07/02 12:58:03 by bfaechti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CREATE TYPE user_status AS ENUM ('Online', 'Offline', 'Playing', 'Away');

CREATE TABLE users (
	id BIGSERIAL PRIMARY KEY,
	username VARCHAR(50) UNIQUE NOT NULL,
	email VARCHAR(255) UNIQUE NOT NULL,
	password_hash VARCHAR(255) NOT NULL,
	status user_status NOT NULL DEFAULT 'Offline',
	creation_date TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP,
	updated_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE friend (
	id BIGSERIAL PRIMARY KEY,
	user_id BIGINT NOT NULL,
	friend_id BIGINT NOT NULL,
	created_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP,

	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
	FOREIGN KEY (friend_id) REFERENCES users(id) ON DELETE CASCADE,
	CHECK (user_id <> friend_id),
	UNIQUE (user_id, friend_id)
);

CREATE TABLE messaging (
	id BIGSERIAL PRIMARY KEY,
	sender_id BIGINT NOT NULL,
	receiver_id BIGINT NOT NULL,
	message TEXT NOT NULL,
	sent_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP,
	is_read BOOLEAN NOT NULL DEFAULT FALSE,

	FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE,
	FOREIGN KEY (receiver_id) REFERENCES users(id) ON DELETE CASCADE,
	CHECK (sender_id <> receiver_id)
);

CREATE INDEX idx_messaging_sender_id
	ON messaging(sender_id);

CREATE INDEX idx_messaging_receiver_id
	ON messaging(receiver_id);

CREATE INDEX idx_messaging_conversation
	ON messaging(sender_id, receiver_id, sent_at DESC);

CREATE TABLE party (
	id BIGSERIAL PRIMARY KEY,
	player1_id BIGINT NOT NULL,
	player2_id BIGINT NOT NULL,
	winner_id BIGINT,
	score_p1 SMALLINT NOT NULL CHECK (score_p1 >= 0),
	score_p2 SMALLINT NOT NULL CHECK (score_p2 >= 0),
	played_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP,

	FOREIGN KEY (player1_id) REFERENCES users(id) ON DELETE CASCADE,
	FOREIGN KEY (player2_id) REFERENCES users(id) ON DELETE CASCADE,
	FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL,
	CHECK (player1_id <> player2_id),
	CHECK (winner_id IS NULL OR winner_id IN (player1_id, player2_id))
);

CREATE INDEX idx_party_player1_id
	ON party(player1_id);

CREATE INDEX idx_party_player2_id
	ON party(player2_id);

CREATE INDEX idx_party_played_at
	ON party(played_at DESC);