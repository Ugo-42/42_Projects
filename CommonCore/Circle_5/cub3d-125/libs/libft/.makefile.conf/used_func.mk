# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    used_func.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 10:27:31 by ugwentzi          #+#    #+#              #
#    Updated: 2025/06/26 15:31:11 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/color.mk

GOLD := \033[1;38;2;147;117;42m

AUTHORIZED_FUNC = \
	write malloc free

IGNORED_FUNC =

IGNORED_MSG := 

used_func:
	@printf "$(GOLD)External Functions:$(RESET)\n"
	@nm -u ./$(NAME) | awk '/^[[:space:]]*U /{print $$2}' | sed 's/@.*//' | \
		sort -u | grep -v '^__' | \
	( \
		suppressed=0; \
		while read func; do \
			auth=0; ignore=0; \
			for allowed in $(AUTHORIZED_FUNC); do \
				[ "$$func" = "$$allowed" ] && auth=1 && break; \
			done; \
			for skipped in $(IGNORED_FUNC); do \
				[ "$$func" = "$$skipped" ] && ignore=1 && break; \
			done; \
			if [ $$auth -eq 1 ]; then \
				printf " $(GOLD)│$(RESET)   — $(GREEN)%s$(RESET)\n" "$$func"; \
			elif [ $$ignore -eq 1 ]; then \
				suppressed=$$((suppressed + 1)); \
			else \
				printf " $(GOLD)│$(RESET)   — $(RED)%s$(RESET)\n" "$$func"; \
			fi; \
		done; \
		if [ $$suppressed -gt 0 ]; then \
			printf " $(GOLD)#$(RESET)   $(ITALIC)%d functions suppressed %s$(RESET)\n" \
				"$$suppressed" "$(IGNORED_MSG)"; \
		fi \
	)

.PHONY: used_func
