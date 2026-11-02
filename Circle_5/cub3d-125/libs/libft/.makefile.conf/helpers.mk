# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    helpers.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 09:43:07 by ugwentzi          #+#    #+#              #
#    Updated: 2025/06/16 13:58:41 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/config.mk

# Debug rule: add debug flags when compiling
debug: clean
	@$(MAKE) DEBUG=1

.PHONY: debug

# **************************************************************************** #
#    Helper function to create the object tree                                 #
#        Exemple: $(call create_object_tree, $(SRCS_DIR), $(OBJS_DIR))         #
# **************************************************************************** #

define create_objs_tree
	@mkdir -p $(OBJS_DIR)
	@find $(1) -type d | sed 's|^$(1)|$(2)|' | xargs mkdir -p
endef

# **************************************************************************** #
#    Helper function to create an exectuable with given objects and libs       #
#        Exemple: $(call build_binary, $(NAME), $(OBJS), $(LIBS), $(COLOR))    #
# **************************************************************************** #

define build_binary
	@$(eval COUNT := 0)
	@$(CC) $(CFLAGS) $(2) $(3) -o $(1)
	@printf "\n$(4)$$ $(1) created successfully!$(RESET)\n"
endef

# **************************************************************************** #
#    Helper function to create an archive with given objects                   #
#       Exemple: $(call build_archive, $(NAME), $(OBJS), $(COLOR))             #
# **************************************************************************** #

define build_archive
	@$(eval COUNT := 0)
	@ar -rcs $(1) $(2)
	@printf "\n$(3)$$ $(1) created successfully!$(RESET)\n"
endef

# **************************************************************************** #
#    Helper function to compile the project ensuring objs dirs creation        #
#        Usage: $(eval $(object_compilation))                                  #
# **************************************************************************** #

define object_compilation
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.${EXT} $(HEADERS)
	$$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$$(YELLOW))
endef

# **************************************************************************** #
#    Helper function to delete objects                                         #
#        Usage: $(call delete_objs)                                            #
# **************************************************************************** #

define delete_objs
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET)\n"
endef

# **************************************************************************** #
#    Helper function to delete binary                                          #
#        Usage: $(call delete_binary)                                          #
# **************************************************************************** #

define delete_binary
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed executable$(RESET)\n"
endef
