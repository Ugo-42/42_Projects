# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:12:34 by ugwentzi          #+#    #+#              #
#    Updated: 2025/03/24 15:18:48 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Launch Valgrind

val:
	@$(MAKE) $(NAME)
	@valgrind \
		--suppressions=minishell.supp \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		-s \
		./$(NAME)
 
.PHONY: val
