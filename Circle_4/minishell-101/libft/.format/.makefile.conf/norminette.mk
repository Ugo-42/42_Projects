# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norminette.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:12:34 by ugwentzi          #+#    #+#              #
#    Updated: 2025/03/22 12:12:34 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Check for Norm Errors

norm:
	@printf "\033[1;38;2;147;117;42mNorminette: \033[0m"
	@norminette | (grep "Error" || echo "No Error!") | awk ' \
	/Error!$$/ { \
		count++; \
		if (count > 1) { print ""; } \
		print "\033[1;38;2;147;117;42m" $$0 "\033[0m"; \
		next; \
	} \
	{ print "\033[0;38;2;94;123;155m" $$0 "\033[0m" }'

.PHONY: norm
