# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norminette.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:12:34 by ugwentzi          #+#    #+#              #
#    Updated: 2025/06/20 14:37:50 by vvalenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Check for Norm Errors

EXCLUDED_PATHS := ./libs/MLX42

# Find all .c and .h files, excluding the above
FIND_EXCLUDES := $(foreach path, $(EXCLUDED_PATHS), ! -path "$(path)/*")
NORM_FILES := $(shell find . -type f \( -name "*.c" -o -name "*.h" \) \
		$(FIND_EXCLUDES))

norm:
	@printf "\033[1;38;2;147;117;42mNorminette: \033[0m"
	@echo "$(NORM_FILES)" | xargs norminette                                  \
	| awk                                                                     \
	'                                                                         \
		/Error!$$/                                                            \
		{                                                                     \
			error_count++;                                                    \
			if (error_count > 1)                                              \
				print "";                                                     \
			print "\033[1;38;2;147;117;42m" $$0 "\033[0m";                    \
			next;                                                             \
		}                                                                     \
		/OK!$$/                                                               \
		{                                                                     \
			next;                                                             \
		}                                                                     \
		{ print "\033[0;38;2;94;123;155m" $$0 "\033[0m"; }                    \
		END                                                                   \
		{                                                                     \
			if (error_count == 0)                                             \
			print "\033[1;38;2;64;148;42mNo Error!\033[0m";                   \
		}                                                                     \
	'

.PHONY: norm

