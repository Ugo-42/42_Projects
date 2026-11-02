# Silence directory entering/exiting message
MAKEFLAGS += --no-print-directory

#=- Config -=#
NAME   = pipex
CC     = cc
CFLAGS = -Wall -Wextra -Werror

#=- Libft -=#
LIBFT_DIR = libft
LIBFT_A   = $(LIBFT_DIR)/libft.a

#=- Directories -=#
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS_DIR_BONUS = bonus_srcs
OBJS_DIR_BONUS = bonus_objs

#=- Sources -=#
INCLUDES = -Iincludes \
           -Ilibft/includes

INCLUDES_BONUS = -Ibonus_includes \
                 -Ilibft/includes

SRCS = main.c \
       ft_execute_command.c \
       ft_exit_error.c \
       ft_get_command_path.c \
       ft_open_files.c \
       ft_open_pipes.c \
       ft_pipex.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

SRCS_BONUS = main_bonus.c \
             ft_execute_command_bonus.c \
             ft_exit_error_bonus.c \
             ft_get_command_path_bonus.c \
             ft_open_files_bonus.c \
             ft_open_pipes_bonus.c \
             ft_pipex_bonus.c \
             ft_handle_here_doc_bonus.c

OBJS_BONUS = $(addprefix $(OBJS_DIR_BONUS)/, $(SRCS_BONUS:.c=.o))

#=- Progress Bar -=#
BAR_LENGTH   = 42
PADDING      = 32 
COLOR_YELLOW = \033[1;33m
COLOR_GREEN  = \033[1;32m
COLOR_CYAN   = \033[1;36m
COLOR_RED    = \033[31m
COLOR_RESET  = \033[0m

#=- Rules -=#
all: $(NAME)

bonus: reset_count $(NAME)_bonus

# Library
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) all

# Executable Creation
$(NAME): $(LIBFT_A) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $@
	@echo
	@printf "$(COLOR_GREEN)$$ $(NAME) created successfully!$(COLOR_RESET)\n"

$(NAME)_bonus: $(LIBFT_A) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) -o $(NAME)_bonus
	@echo
	@printf "$(COLOR_GREEN)$$ $(NAME)_bonus created successfully! $(COLOR_RESET)\n"

# Objects Creation
$(OBJS_DIR) $(OBJS_DIR_BONUS):
	@mkdir -p $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(call compile_object, $(INCLUDES), $(SRCS), $(COLOR_YELLOW))

$(OBJS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c | $(OBJS_DIR_BONUS)
	$(call compile_object, $(INCLUDES_BONUS), $(SRCS_BONUS), $(COLOR_CYAN))

# Clean Rules
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR) $(OBJS_DIR_BONUS)
	@printf "$(COLOR_RED)$$ $(NAME): Removed objects$(COLOR_RESET)\n"

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJS_DIR) $(OBJS_DIR_BONUS)
	@printf "$(COLOR_RED)$$ $(NAME): Removed objects$(COLOR_RESET)\n"
	@rm -f $(NAME) $(NAME)_bonus
	@printf "$(COLOR_RED)$$ $(NAME): Removed executables$(COLOR_RESET)\n"

re: fclean all

reset_count:
	$(eval COUNT := 0)

# Helper function to print a progress bar
# Credits: ugwentzi@student.42mulhouse.fr
define compile_object
$(eval COUNT := $(shell echo $$(( $(COUNT) + 1 ))))
@$(CC) $(CFLAGS) $(1) -c $< -o $@
@printf "\r$(3)\bCompiling %s%*s[%-$(BAR_LENGTH)s] %d/%d$(COLOR_RESET)" \
	"$(NAME)" \
	$$(($(PADDING) - $$(echo -n "$(NAME)" | wc -c))) "" \
	$(shell printf '=%.0s' $$(seq 1 $$(echo "$$(( $(BAR_LENGTH) * $(COUNT) / $(words $(2)) ))"))) \
	$(COUNT) \
	$(words $(2))
@true
endef

.PHONY: all bonus clean fclean re
