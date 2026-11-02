# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 19:11:07 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/22 15:19:36 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Set the rule all by default (for `make` without args)
.DEFAULT_GOAL := all

# Silence the `Entering/Leaving directory` message
MAKEFLAGS += --no-print-directory

# **************************************************************************** #
#                                Compilation                                   #
# **************************************************************************** #

LANGAGE := cpp

ifeq ($(LANGAGE), c)
	CC     = cc
	EXT    = c
	CFLAGS = -Wall -Wextra -Werror
else
	CC     = c++
	EXT    = cpp
	CFLAGS = -Wall -Wextra -Werror -std=c++98
endif

# **************************************************************************** #
#                      COMPILATION FLAGS (special rules)                       #
# **************************************************************************** #

# Comment to disable colors
CFLAGS += -D COLOR_ON

# DEBUG Mode (disabled by default)
DEBUG_FLAG :=
ifdef DEBUG
    DEBUG_FLAG = -D DEBUG=1 -g3
endif

CFLAGS += $(DEBUG_FLAG)
