# Silence directory entering/exiting message
MAKEFLAGS += --no-print-directory

#=- Config -=#
NAME   = libft.a
CC     = cc
CFLAGS = -Wall -Wextra -Werror

#=- Directories -=#
SRCS_DIR = srcs
OBJS_DIR = objs

#=- Sources -=#
INCLUDES = -Iincludes

SRCS = allocation/ft_calloc.c \
       allocation/ft_realloc.c \
       allocation/ft_free_2d_array.c \
       conversion/ft_atoi.c \
       conversion/ft_itoa.c \
       conversion/ft_tolower.c \
       conversion/ft_toupper.c \
       count/ft_count_words.c \
       count/ft_count_words_quoted.c \
       count/ft_strlen.c \
       is/ft_isalnum.c \
       is/ft_isalpha.c \
       is/ft_isascii.c \
       is/ft_isdigit.c \
       is/ft_isprint.c \
       is/ft_isquote.c \
       is/ft_isspace.c \
       list/ft_lstadd_back.c \
       list/ft_lstadd_front.c \
       list/ft_lstclear.c \
       list/ft_lstdelone.c \
       list/ft_lstiter.c \
       list/ft_lstlast.c \
       list/ft_lstmap.c \
       list/ft_lstnew.c \
       list/ft_lstsize.c \
       memory/ft_bzero.c \
       memory/ft_memchr.c \
       memory/ft_memcmp.c \
       memory/ft_memcpy.c \
       memory/ft_memmove.c \
       memory/ft_memset.c \
       other/ft_segfault.c \
       print/ft_fprintf.c \
       print/ft_print_address_fd.c \
       print/ft_print_hex_fd.c \
       print/ft_printf.c \
       print/ft_putchar_fd.c \
       print/ft_putnbr_fd.c \
       print/ft_putstr_fd.c \
       print/ft_putstrn_fd.c \
       print/ft_putunbr_fd.c \
       read/get_next_line.c \
       skip/ft_skip_chars.c \
       skip/ft_skip_not_chars.c \
       skip/ft_skip_quoted.c \
       skip/ft_skip_spaces.c \
       skip/ft_skip_word.c \
       string/ft_split.c \
       string/ft_split_quoted.c \
       string/ft_str_ultimate_join.c \
       string/ft_strchr.c \
       string/ft_strcmp.c \
       string/ft_strcpy.c \
       string/ft_strdup.c \
       string/ft_strjoin.c \
       string/ft_strncmp.c \
       string/ft_strncpy.c \
       string/ft_strnstr.c \
       string/ft_strrchr.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#=- Progress Bar -=#
BAR_LENGTH   = 42
PADDING      = 32
COLOR_YELLOW = \033[1;33m
COLOR_GREEN  = \033[1;32m
COLOR_RED    = \033[31m
COLOR_RESET  = \033[0m

#=- Rules -=#
all: $(NAME)

# Archive Creation
$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo
	@printf "$(COLOR_GREEN)$$ $(NAME) created successfully!$(COLOR_RESET)\n"

# Objects Creation
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@find $(SRCS_DIR) -type d | sed 's/^$(SRCS_DIR)/$(OBJS_DIR)/' | xargs mkdir -p

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(call compile_object, $(INCLUDES), $<, $@, $(SRCS), $(COLOR_YELLOW))

# Clean Rules
clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(COLOR_RED)$$ $(NAME): Removed objects$(COLOR_RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(COLOR_RED)$$ $(NAME): Removed $(NAME)$(COLOR_RESET)\n"

re: fclean all

# Helper function to print a progress bar
# Credits: ugwentzi@student.42mulhouse.fr
define compile_object
@$(eval COUNT := $(shell echo $$(( $(COUNT) + 1 ))))
@$(CC) $(CFLAGS) $(1) -c $(2) -o $(3)
@printf "\r$(5)\bCompiling %s%*s[%-$(BAR_LENGTH)s] %d/%d$(COLOR_RESET)" \
	"$(NAME)" \
	$$(($(PADDING) - $$(echo -n "$(NAME)" | wc -c))) "" \
	$(shell printf '=%.0s' $$(seq 1 $$(echo "$$(( $(BAR_LENGTH) * $(COUNT) / $(words $(4)) ))"))) \
	$(COUNT) \
	$(words $(4))
@true
endef

.PHONY: all clean fclean re
