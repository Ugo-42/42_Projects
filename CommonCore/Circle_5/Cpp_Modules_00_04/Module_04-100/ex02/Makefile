# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/11/19 11:35:00 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/headers.mk

NAME = Animal

SRCS_DIR = srcs
OBJS_DIR = .objs
HEADERS  = includes
INCLUDES = $(addprefix -I, $(HEADERS))

SRCS = main.cpp Animal.cpp Brain.cpp Cat.cpp Dog.cpp 
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.${EXT}=.o))

# ********************************************************** #
#                          RULES                             #
# ********************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),$(LDFLAGS),$(BOLD)$(GREEN))
	@if [ "$(LANGAGE)" = "c" ]; then \
		$(MAKE) used_func; \
		$(MAKE) norm; \
	fi

$(eval $(object_compilation))

clean:
	$(call delete_objs)

fclean:
	$(call delete_objs)
	$(call delete_binary)

re: fclean all

.PHONY: all clean fclean re
