# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 10:16:23 by ugwentzi          #+#    #+#              #
#    Updated: 2025/02/17 10:23:47 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include makefile.conf/color.mk
include makefile.conf/compilation.mk
include makefile.conf/config.mk
include makefile.conf/libft.mk
include makefile.conf/progress_bar.mk

#=- Name -=#
NAME_1 = push_swap
NAME_2 = checker

#=- Directories -=#
SRCS_DIR = srcs
OBJS_DIR = objs

#=- Bonus Directories -=#
BONUS_SRCS_DIR = bonus_srcs
BONUS_OBJS_DIR = bonus_objs

#=- Sources -=#
INCLUDES = -Iincludes \
           -Ilibft/includes

SRCS = main.c \
       ft_algorithm.c \
       ft_check_valid_stack.c \
       ft_helper.c \
       ft_initializations.c \
       ft_push_swap.c \
       instructions/ft_combine.c \
       instructions/ft_print_instruction.c \
       instructions/ft_push.c \
       instructions/ft_reverse_rotate.c \
       instructions/ft_rotate.c \
       instructions/ft_swap.c \
       instructions/ft_write_instruction.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#=- Bonus Sources -=#

BONUS_INCLUDES = -Ibonus_includes \
                 -Ilibft/includes

BONUS_SRCS = main.c \
             ft_check_valid_stack.c \
             ft_checker.c \
             ft_helper.c \
             ft_initializations.c \
             instructions/ft_execute_instruction.c \
             instructions/ft_is_valid_instruction.c \
             instructions/ft_push.c \
             instructions/ft_reverse_rotate.c \
             instructions/ft_rotate.c \
             instructions/ft_swap.c

BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

#=- RULES -=#
all: $(NAME_1) $(NAME_2)

bonus: $(NAME_2)
### PUSH_SWAP ###

#=- Executable Creation -=#
$(NAME_1): $(LIBFT_A) $(OBJS)
	$(call build_binary,$(NAME_1),$(OBJS),$(LIBFT_A),$(BOLD)$(GREEN))

#=- Objects Compilation -=#
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME_1),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

### CHECKER ###

#=- Bonus Executable Creation -=#
$(NAME_2): $(LIBFT_A) $(BONUS_OBJS)
	$(call build_binary,$(NAME_2),$(BONUS_OBJS),$(LIBFT_A),$(BOLD)$(GREEN))

#=- Bonus Objects Compilation -=#
$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	$(call create_objs_tree,$(BONUS_SRCS_DIR),$(BONUS_OBJS_DIR))
	$(call compile_object,$(NAME_2),$(BONUS_INCLUDES),$(BONUS_SRCS),$(BOLD)$(YELLOW))

### CLEAN RULES ###
clean: clean_libft
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME_1): Removed objects$(RESET_COLOR)\n"
	@rm -rf $(BONUS_OBJS_DIR)
	@printf "$(RED)$$ $(NAME_2): Removed objects$(RESET_COLOR)\n"

fclean: fclean_libft
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME_1): Removed objects$(RESET_COLOR)\n"
	@rm -f $(NAME_1)
	@printf "$(RED)$$ $(NAME_1): Removed executable$(RESET_COLOR)\n"
	@rm -rf $(BONUS_OBJS_DIR)
	@printf "$(RED)$$ $(NAME_2): Removed objects$(RESET_COLOR)\n"
	@rm -f $(NAME_2)
	@printf "$(RED)$$ $(NAME_2): Removed executable$(RESET_COLOR)\n"

### RECOMPILATION RULES ###
re: fclean all

.PHONY: all bonus clean fclean re
