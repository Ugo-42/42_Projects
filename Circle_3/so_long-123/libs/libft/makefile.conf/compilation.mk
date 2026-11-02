# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    progress_bar.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 09:43:07 by ugwentzi          #+#    #+#              #
#    Updated: 2025/02/13 10:27:05 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include makefile.conf/config.mk

# Fancy rule: make the program fancier (if the dev supported it)
fancy: fclean
	@$(MAKE) FANCY=1

# Debug rule: add debug flags when compiling
debug: fclean
	@$(MAKE) DEBUG=1

# Helper function to create the object tree
# Exemple: $(call create_object_tree, $(SRCS_DIR), $(OBJS_DIR))

define create_objs_tree
	@mkdir -p $(OBJS_DIR)
	@find $(1) -type d | sed 's|^$(1)|$(2)|' | xargs mkdir -p
endef

# Helper function to create an exectuable with given objects and libs
# Exemple: $(call build_binary, $(NAME), $(OBJS), $(LIBS), $(COLOR))

define build_binary
	@$(eval COUNT := 0)
	@$(CC) $(CFLAGS) $(2) $(3) -o $(1)
	@printf "\n$(4)$$ $(1) created successfully!$(RESET_COLOR)\n"
endef

# Helper function to create an archive with given objects
# Exemple: $(call build_archive, $(NAME), $(OBJS), $(COLOR))

define build_archive
	@$(eval COUNT := 0)
	@ar -rcs $(1) $(2)
	@printf "\n$(3)$$ $(1) created successfully!$(RESET_COLOR)\n"
endef

