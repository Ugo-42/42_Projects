#┌─────────────────────────────────────────────────────────────────────────────┐#
#│                                                                             │#
#│   valgrind.mk                                            ▒▒▒▒    ▒▒▒▒       │#
#│                                                          ▒▒▒▒    ▒▒▒▒       │#
#│   By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒           │#
#│                                                            ▒▒▒▒▒▒▒▒         │#
#│   Created: 2026/02/17 11:22:06 by ugwentzi                 ▒▒▒▒▒▒▒▒         │#
#│   Updated: 2026/02/17 11:22:06 by ugwentzi                 ▒▒    ▒▒         │#
#│                                                                             │#
#└─────────────────────────────────────────────────────────────────────────────┘#

# Launch Valgrind

SUPP_OPTION =

OPTIONS = --leak-check=full \
          --show-leak-kinds=all \
          --track-origins=yes \
          --track-fds=yes \
          -s \

val:
	@printf '\033[H\033[2J'
	@$(MAKE) $(NAME)
	@valgrind \
		$(SUPP_OPTION) \
		$(OPTIONS) \
		./$(NAME)

eval:
	@bash -ic ' \
		tmp=$$(mktemp); \
		printf "%s\n" \
		"valgrind \\" \
		"    $(SUPP_OPTION) \\" \
		"    $(OPTIONS) \\" \
		"    ./$(NAME)" \
		> $$tmp; \
		$${EDITOR:-vim} -c "autocmd VimEnter * normal! G$$" $$tmp; \
		bash $$tmp; \
		rm $$tmp \
		'
 
.PHONY: val
