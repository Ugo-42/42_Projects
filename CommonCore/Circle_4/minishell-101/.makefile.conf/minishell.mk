# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    minishell.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 19:11:07 by ugwentzi          #+#    #+#              #
#    Updated: 2025/04/07 13:01:29 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# config headers
include .makefile.conf/color.mk
include .makefile.conf/compilation.mk
include .makefile.conf/config.mk
include .makefile.conf/lldb.mk
include .makefile.conf/norminette.mk
include .makefile.conf/progress_bar.mk
include .makefile.conf/valgrind.mk

# libs headers
include .makefile.conf/libft.mk
