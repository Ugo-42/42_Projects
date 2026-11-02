# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/22 13:48:45 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/philosophers.mk

NAME = philo

SRCS_DIR = srcs
OBJS_DIR = objs
HEADERS  = includes
INCLUDES = $(addprefix -I, $(HEADERS))

#CFLAGS   += -fsanitize=thread

SRCS = main.c parse_args.c routine.c initializations.c grim_reaper.c \
	   utils/atoi.c \
	   utils/print_error.c \
       utils/current_time_ms.c \
       utils/print_status.c \
       utils/print_usage.c \
       utils/prefix_color.c \
       utils/strlen.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#=- RULES -=#
all: $(NAME)

$(NAME): $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),,$(BOLD)$(GREEN))
	@$(MAKE) used_func
	@$(MAKE) norm

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET)\n"

fclean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed executable$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
