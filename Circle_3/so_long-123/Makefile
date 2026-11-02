# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/03/07 11:45:56 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/so_long.mk

NAME = so_long
BONUS_NAME = so_long_bonus

LIBS = $(LIBMLX_A) -lglfw -lm $(LIBFT_A)

#=- SO_LONG -=#
SRCS_DIR = common/srcs
OBJS_DIR = common/objs

INCLUDES = -Icommon/includes \
           -Ilibs/libft/includes \
           -Ilibs/MLX42/include/MLX42

SRCS = main.c \
	   check_path.c \
	   cleanup.c \
	   init_sprites.c \
	   input.c \
	   window_managment.c \
       parse_map.c \
       read_ber.c \
       so_long.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#=- SO_LONG BONUS -=#
BONUS_SRCS_DIR = bonus/bonus_srcs
BONUS_OBJS_DIR = bonus/bonus_objs

BONUS_INCLUDES = -Ibonus/bonus_includes \
                 -Ilibs/libft/includes \
                 -Ilibs/MLX42/include/MLX42

BONUS_SRCS = main_bonus.c \
			 print_text_bonus.c \
	         check_path_bonus.c \
	         cleanup_bonus.c \
	         init_sprites_bonus.c \
	         input_bonus.c \
	         window_managment_bonus.c \
             parse_args_bonus.c \
             parse_map_bonus.c \
             read_ber_bonus.c \
             so_long_bonus.c \
			 endless_mode/endless_bonus.c \
			 story_mode/story_bonus.c \
			 map_gen/carve_bonus.c \
			 map_gen/map_gen_bonus.c \
			 map_gen/save_map_bonus.c \
			 map_gen/create_map_bonus.c \
			 story_mode/black_hole_bonus.c \
			 story_mode/black_hole_animation_bonus.c \
			 story_mode/story_checks_bonus.c \
             story_mode/init_black_hole_bonus.c

BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

#=- RULES -=#
all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(LIBS) $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),$(LIBS),$(BOLD)$(GREEN))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

$(BONUS_NAME): $(LIBS) $(BONUS_OBJS)
	$(call build_binary,$(BONUS_NAME),$(BONUS_OBJS),$(LIBS),$(BOLD)$(CYAN))

$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	$(call create_objs_tree,$(BONUS_SRCS_DIR),$(BONUS_OBJS_DIR))
	$(call compile_object,$(BONUS_NAME),$(BONUS_INCLUDES),$(BONUS_SRCS),$(BOLD)$(MAGENTA))

clean: clean_libft
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"
	@rm -rf $(BONUS_OBJS_DIR)
	@printf "$(RED)$$ $(BONUS_NAME): Removed objects$(RESET_COLOR)\n"

fclean: fclean_libft fclean_libmlx
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"
	@rm -rf $(BONUS_OBJS_DIR)
	@printf "$(RED)$$ $(BONUS_NAME): Removed objects$(RESET_COLOR)\n"
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed executable$(RESET_COLOR)\n"
	@rm -f $(BONUS_NAME)
	@printf "$(RED)$$ $(BONUS_NAME): Removed executable$(RESET_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
