# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:12:34 by ugwentzi          #+#    #+#              #
#    Updated: 2025/04/25 11:33:35 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Launch Valgrind

SUPP_OPTION = --suppressions=minishell.supp

OPTIONS = --leak-check=full \
          --show-leak-kinds=all \
          --track-origins=yes \
          --track-fds=yes \
          -s \

val:
	@clear
	@$(MAKE) $(NAME)
	@valgrind \
		$(SUPP_OPTION) \
		$(OPTIONS) \
		./$(NAME)
 
.PHONY: val
