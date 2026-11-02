# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    used_func.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 10:27:31 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/20 14:50:12 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/color.mk
GOLD := \033[1;38;2;147;117;42m

AUTHORIZED_FUNC = \
	memset                printf                  malloc \
	free                  write                   usleep \
	gettimeofday          pthread_create          pthread_detach \
	pthread_join          pthread_mutex_init      pthread_mutex_destroy \
	pthread_mutex_lock    pthread_mutex_unlock

used_func:
	@printf "$(GOLD)External Functions:$(RESET)\n"
	@nm -u ./$(NAME) |                                                         \
	awk '/^[[:space:]]*U /{print $$2}' | sed 's/@.*//' | sort -u |             \
	while read func; do                                                        \
		authorized=0;                                                          \
		for allowed in $(AUTHORIZED_FUNC); do                                  \
			[ "$$func" = "$$allowed" ] && authorized=1 && break;               \
		done;                                                                  \
		if [ $$authorized -eq 1 ]; then                                        \
			printf " $(GOLD)│$(RESET)   — $(GREEN)%s$(RESET)\n" "$$func";      \
		else                                                                   \
			printf " $(GOLD)│$(RESET)   — $(RED)%s$(RESET)\n" "$$func";        \
		fi;                                                                    \
	done

.PHONY: used_func
