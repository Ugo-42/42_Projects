# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 10:00:32 by ugwentzi          #+#    #+#              #
#    Updated: 2025/06/10 11:00:35 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# libft compilation and clean rules

LIBFT_DIR = libs/libft
LIBFT_A   = $(LIBFT_DIR)/libft.a
LIBFT_H   = $(LIBFT_DIR)/includes

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) all

clean_libft:
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean_libft:
	@$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: clean_libft fclean_libft
