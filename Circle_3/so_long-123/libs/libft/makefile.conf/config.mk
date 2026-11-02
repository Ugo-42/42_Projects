# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 19:11:07 by ugwentzi          #+#    #+#              #
#    Updated: 2025/01/08 19:11:12 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Set the rule all by default (for `make` without args)
.DEFAULT_GOAL := all

# Silence the `Entering/Leaving directory` message
MAKEFLAGS += --no-print-directory

# Compilation
CC     = cc
CFLAGS = -Wall -Wextra -Werror

### COMPILATION FLAGS (special rules) ###

# FANCY Mode (disabled by default)
FANCY_FLAG :=
ifdef FANCY
    FANCY_FLAG = -DFANCY=1
endif

CFLAGS += $(FANCY_FLAG)

# DEBUG Mode (disabled by default)
DEBUG_FLAG :=
ifdef DEBUG
    DEBUG_FLAG = -g3 #-fsanitize=address,undefined
endif

CFLAGS += $(DEBUG_FLAG)
