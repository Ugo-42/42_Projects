# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/08/25 15:46:23 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/headers.mk

NAME = cub3D

SRCS_DIR = srcs
OBJS_DIR = .objs
HEADERS  = includes $(LIBFT_H) $(LIBMLX_H)
INCLUDES = $(addprefix -I, $(HEADERS))

LIBS = $(LIBFT_A) $(LIBMLX_A) -lglfw -lm

# Functions: 30
SRCS = main.c                                  cub3d_/cub3d.c \
       cub3d_/menu.c                           cub3d_/menu_settings.c \
       cub3d_/menu_updates.c                   cub3d_/draw_map.c \
       init/initializations.c                  init/load_textures.c \
       init/init_menu.c                        init/init_utils.c \
       input/handle_movement.c                 input/handle_rotation.c \
       input/movement.c                        loops/fps.c \
       loops/loops.c                           parsing/map_check.c \
       parsing/parsing.c                       ray_casting/ray_casting.c \
       ray_casting/rc_maths.c                  ray_casting/rc_rendering.c \
       ray_casting/rc_texture.c                utils/cleanup.c \
       utils/clear_image.c                     utils/is_utils.c \
       utils/is_utils2.c                       utils/print_utils.c \
       utils/window_managment.c                utils/ft_atou.c \
       _benchmark/_benchmark.c                 _benchmark/_disabled.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.${EXT}=.o))

CFLAGS += -g3 -O3 #-fsanitize=address,undefined,leak

# ********************************************************** #
#                          RULES                             #
# ********************************************************** #

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),$(LIBS),$(BOLD)$(GREEN))
	@if [ "$(LANGAGE)" = "c" ]; then \
		$(MAKE) used_func; \
	fi

$(eval $(object_compilation))

clean: clean_libft
	$(call delete_objs)

fclean: fclean_libft fclean_libmlx
	$(call delete_objs)
	$(call delete_binary)

re: clean all

noerr:
	@$(MAKE) CFLAGS+=" -Wno-error" clean all


.PHONY: all clean fclean re noerr
