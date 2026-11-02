# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    progress_bar.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 09:43:07 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/16 11:03:12 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Helper function to print a progress bar
# Exemple: $(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(COLOR))

BAR_LENGTH := 42
PADDING    := 32

define compile_object
    @$(eval COUNT := $(shell echo $$(( $(COUNT) + 1 ))))
	@$(CC) $(CFLAGS) $(2) -c $< -o $@
	@printf "\r$(4)Compiling $(1)"
    @printf "%*s[%-$(BAR_LENGTH)s] %d/%d$(RESET)" \
        $$(($(PADDING) - $$(echo -n "$(1)" | wc -c))) "" \
        $(shell printf '=%.0s' $$(seq 1 $$(echo \
	        $$(( $(BAR_LENGTH) * $(COUNT) / $(words $(3)) ))))) \
        $(COUNT) \
        $(words $(3))
    @true
endef
