#┌─────────────────────────────────────────────────────────────────────────────┐#
#│                                                                             │#
#│   Makefile                                               ▒▒▒▒    ▒▒▒▒       │#
#│                                                          ▒▒▒▒    ▒▒▒▒       │#
#│   By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒           │#
#│                                                            ▒▒▒▒▒▒▒▒         │#
#│   Created: 2026/02/17 11:22:37 by ugwentzi                 ▒▒▒▒▒▒▒▒         │#
#│   Updated: 2026/02/17 11:22:37 by ugwentzi                 ▒▒    ▒▒         │#
#│                                                                             │#
#└─────────────────────────────────────────────────────────────────────────────┘#

include .makefile.conf/headers.mk

NAME = webserv

SRCS_DIR = srcs
OBJS_DIR = .objs
HEADERS  = includes
INCLUDES = $(addprefix -I, $(HEADERS))

SRCS = main.cpp \
	   server/Server.cpp \
	   server/Request.cpp \
	   server/Response.cpp \
	   server/Location.cpp \
	   server/Router.cpp \
	   server/ServerManager.cpp \
       parsing/parser.cpp \
	   parsing/tokenizer.cpp \
	   parsing/sub_parser/helper.cpp \
	   parsing/sub_parser/parse_server.cpp \
	   parsing/sub_parser/parse_location.cpp

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.${EXT}=.o))

CC      = c++
EXT     = cpp
CFLAGS  = -Wall -Wextra -Werror -std=c++98 -g3

#┌───────────────────────────────────────────────────────────────┐#
#│                             RULES                             │#
#└───────────────────────────────────────────────────────────────┘#

all: $(NAME)

$(NAME): $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),$(LDFLAGS),$(BOLD)$(GREEN))

$(eval $(object_compilation))

clean:
	$(call delete_objs)

fclean:
	$(call delete_objs)
	$(call delete_binary)

re: fclean all

.PHONY: all clean fclean re
