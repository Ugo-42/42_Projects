# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/11/21 13:22:32 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/headers.mk

NAME = Interface

SRCS_DIR = srcs
OBJS_DIR = .objs
HEADERS  = includes
INCLUDES = $(addprefix -I, $(HEADERS))

SRCS = main.cpp \
	   AMateria.cpp \
	   Character.cpp \
	   Cure.cpp \
	   Ice.cpp \
	   MateriaSource.cpp
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
