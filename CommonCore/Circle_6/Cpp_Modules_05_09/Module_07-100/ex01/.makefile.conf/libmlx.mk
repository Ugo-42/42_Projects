# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libmlx.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 10:00:32 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/16 11:02:59 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# mlx42 compilation and clean rules

LIBMLX_DIR = libs/MLX42
LIBMLX_A   = $(LIBMLX_DIR)/build/libmlx42.a

$(LIBMLX_A):
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@make -C $(LIBMLX_DIR)/build -j4

fclean_libmlx:
	@rm -rf $(LIBMLX_DIR)/build
	@printf "$(RED)$$ libmlx: Removed objects$(RESET)\n"
	@printf "$(RED)$$ libmlx: Removed executable$(RESET)\n"

.PHONY: fclean_libmlx
