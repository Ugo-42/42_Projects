export DOCKER_BUILDKIT=1

LOGIN = ugwentzi

all: init build up

init:
	@if [ ! -f srcs/.env ]; then \
		echo "\033[1;31mError:\033[0;31m no srcs/.env file, required for docker build.\033[0m"; \
		exit 1; \
	fi
	@sudo -v
	@echo "Creating host data directories..."
	@mkdir -p ~/data/mariadb ~/data/wordpress
	@echo "Setting permissions for volumes..."
	@sudo chmod -R 777 ~/data/mariadb ~/data/wordpress
	@sudo -k

build:
	@echo "Building Docker images..."
	@docker compose -f srcs/docker-compose.yml build

up:
	@echo "Starting containers..."
	@docker compose -f srcs/docker-compose.yml up -d

down:
	@echo "Stopping containers..."
	@docker compose -f srcs/docker-compose.yml down

stop:
	@echo "Stopping containers..."
	@docker compose -f srcs/docker-compose.yml stop

start:
	@echo "Starting containers..."
	@docker compose -f srcs/docker-compose.yml start

restart: down up

logs:
	@docker compose -f srcs/docker-compose.yml logs -f

clean: down
	@echo "Cleaning up containers and images..."
	@docker system prune -af

fclean:
	@sudo -v
	@echo "Stopping and removing containers..."
	@docker compose -f srcs/docker-compose.yml down -v 2>/dev/null || true
	@echo "Cleaning up containers and images..."
	@docker system prune -af
	@echo "Removing data directories..."
	@sudo rm -rf ~/data/wordpress ~/data/mariadb
	@sudo -k

re: fclean all

status:
	@docker compose -f srcs/docker-compose.yml ps

nuclear_docker_nuke:
	@sudo -v
	@for i in 3 2 1; do \
		printf "\033[1;31m$$i\033[0m\n"; \
		sleep 0.33; \
	done
	@printf "\033[1;33m\n\
                             ____\n\
                       __,-~~/~    \`---.\n\
                     _/_,---(      ,    )\n\
               __ /        <    /    )  \\\\\n\
\033[93m- ------===;;;'====------------------===;;;===----- -   -\033[33m\n\
                   \\\/  ~\"~\"~\"~\"~\"~\\\\~\"~)~\"/\n\
                   (_ (    \\\\  (     >    \\\\)\n\
                    \\\\_( _ <         >_>'\n\
                      ~ \`-i' ::>|--\"\n\
                          I;|.|.|\n\
                         <|i::|i|\\\`.\n\
                        (\` ^'\"\`-' \")\n\
              _ ___ _---==-----------=--____ _ _   \n\
\033[0m\n"
	@docker compose -f srcs/docker-compose.yml down -v 2>/dev/null || true
	@docker system prune -a --volumes -f
	@docker builder prune -af
	@docker rmi -f $$(docker images -aq) 2>/dev/null || true
	@sudo rm -rf ~/data/wordpress ~/data/mariadb
	@sudo -k

.PHONY: all init build up down stop start restart logs clean fclean re status nuclear_docker_nuke
