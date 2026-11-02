# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    color.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:12:34 by ugwentzi          #+#    #+#              #
#    Updated: 2025/01/08 14:49:16 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Text Styles
RESET_COLOR     :=  \033[0m
BOLD            :=  \033[1m
DIM             :=  \033[2m
ITALIC          :=  \033[3m
LOW_LINE        :=  \033[4m
BLINK           :=  \033[5m
REVERSE         :=  \033[7m
HIDDEN          :=  \033[8m
STRIKE          :=  \033[9m
DOUBLE_LOW_LINE :=  \033[21m
TOP_LINE        :=  \033[53m
TOP_LOW_LINE    :=  \033[4;53m

# Text Basic Colors
BLACK           :=  \033[30m
RED             :=  \033[31m
GREEN           :=  \033[32m
YELLOW          :=  \033[33m
BLUE            :=  \033[34m
MAGENTA         :=  \033[35m
CYAN            :=  \033[36m
WHITE           :=  \033[37m

# Text High Intensity Colors
IBLACK          :=  \033[90m
IRED            :=  \033[91m
IGREEN          :=  \033[92m
IYELLOW         :=  \033[93m
IBLUE           :=  \033[94m
IMAGENTA        :=  \033[95m
ICYAN           :=  \033[96m
IWHITE          :=  \033[97m

# Background Colors
BG_BLACK        :=  \033[40m
BG_RED          :=  \033[41m
BG_GREEN        :=  \033[42m
BG_YELLOW       :=  \033[43m
BG_BLUE         :=  \033[44m
BG_MAGENTA      :=  \033[45m
BG_CYAN         :=  \033[46m
BG_WHITE        :=  \033[47m

# Background High Intensity Colors
BG_IBLACK       :=  \033[100m
BG_IRED         :=  \033[101m
BG_IGREEN       :=  \033[102m
BG_IYELLOW      :=  \033[103m
BG_IBLUE        :=  \033[104m
BG_IMAGENTA     :=  \033[105m
BG_ICYAN        :=  \033[106m
BG_IWHITE       :=  \033[107m
