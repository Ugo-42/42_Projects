# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/03/27 12:15:26 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/format_files.mk

NAME = fs

SRCS_DIR = srcs
OBJS_DIR = objs
HEADERS  = includes
INCLUDES = $(addprefix -I, $(HEADERS))

SRCS = format_files.c \
	   format_files_print.c \
	   format_files_utils.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
LIBS =

#=- RULES -=#
all: norm $(NAME)

$(NAME): $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),$(LIBS),$(BOLD)$(GREEN))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"

fclean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed executable$(RESET_COLOR)\n"

re: clean all
relib: fclean all

.PHONY: all clean fclean re relib
