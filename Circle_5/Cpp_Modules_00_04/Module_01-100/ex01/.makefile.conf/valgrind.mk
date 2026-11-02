# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:12:34 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/22 15:05:48 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Launch Valgrind

SUPP_OPTION =

OPTIONS = --leak-check=full \
          --show-leak-kinds=all \
          --track-origins=yes \
          --track-fds=yes \
          -s \

val:
	@printf '\033[H\033[2J'
	@$(MAKE) $(NAME)
	@valgrind \
		$(SUPP_OPTION) \
		$(OPTIONS) \
		./$(NAME)
 
.PHONY: val
