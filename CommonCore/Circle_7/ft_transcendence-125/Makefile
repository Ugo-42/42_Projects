NAME := transcendence

all: init up

init:
	@if [ ! -f .env ]; then \
		printf "\e[1;31mError:\e[0;38;2;255;155;155m no \`.env\` file, required for docker build.\e[0m\n"; \
		exit 1; \
	fi

up:
	docker compose up --build -d

down:
	docker compose down -v

status:
	docker compose ps

logs:
	docker compose logs -f

clean:
	docker compose down -v --rmi all

env:
	cp .env.example .env
	cp backend/game-service/.env.game-service.example backend/game-service/.env.game-service
	cp backend/socket-service/.env.socket-service.example backend/socket-service/.env.socket-service
	cp backend/user-service/.env.user-service.example backend/user-service/.env.user-service

nuclear_nuke:
	@set -e; \
	ruby .fun/nuke.rb; \
	ruby .fun/player.rb .fun/nuke.ascii & \
	ANIM_PID=$$!; \
	docker stop $$(docker ps -aq) > /dev/null 2>&1 || true; \
	docker rm -f $$(docker ps -aq) > /dev/null 2>&1 || true; \
	docker network prune -f > /dev/null 2>&1; \
	docker volume prune -f > /dev/null 2>&1; \
	docker rmi -f $$(docker images -q) > /dev/null 2>&1 || true; \
	docker builder prune -af > /dev/null 2>&1; \
	docker system prune -af > /dev/null 2>&1; \
	kill $$ANIM_PID 2>/dev/null; \
	printf "\e[?25h\e[2J\e[H\e[32mCleanup complete!\n"

re: down up

dev: init
	docker compose -f docker-compose.yml -f docker-compose.dev.yml up --build -d

dev-down:
	docker compose -f docker-compose.yml -f docker-compose.dev.yml down

.PHONY: all up down status logs clean nuclear_nuke re dev dev-down
