# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/05/09 09:51:06 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/minishell.mk

NAME = minishell

SRCS_DIR = srcs
OBJS_DIR = objs
HEADERS  = includes libft/includes
INCLUDES = $(addprefix -I, $(HEADERS))

# Functions: 45
SRCS = main.c                                  built_in/exec_binary.c \
       built_in/exec_cd.c                      built_in/exec_echo.c \
       built_in/exec_env.c                     built_in/exec_exit.c \
       built_in/exec_export.c                  built_in/exec_pwd.c \
       built_in/exec_unset.c                   debug/debug_print.c \
       debug/debug_print_2d.c                  debug/debug_print_commands.c \
       debug/debug_print_redirections.c        debug/debug_print_type.c \
       execution/command_executor.c            execution/execute_commands.c \
       execution/handle_heredoc.c              execution/handle_pipe.c \
       execution/handle_redirections.c         parsing/assign_types.c \
       parsing/check_input_error.c             parsing/commands_check.c \
       parsing/expand_heredoc.c                parsing/expand_tokens.c \
       parsing/expand_vars.c                   parsing/parse_input.c \
       parsing/separate_operators.c            parsing/split_commands.c \
       parsing/split_redirections.c            shell/cleanup.c \
       shell/handle_fd.c                       shell/init_shell.c \
       shell/input_cleanup.c                   shell/prompt.c \
       signal/handle_signal.c                  signal/heredoc_signal.c \
       signal/restore_signal.c                 signal/set_signal.c \
       utils/convert_exit_status.c             utils/get_command_path.c \
       utils/get_env_var.c                     utils/is_utils.c \
       utils/in_tty.c                          utils/pipe_utils.c \
       utils/strdup_reject.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
LIBS = $(LIBFT_A) -lreadline -lncurses

#=- RULES -=#
all: norm $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(call build_binary,$(NAME),$(OBJS),$(LIBS),$(BOLD)$(GREEN))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

clean: clean_libft
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"

fclean: fclean_libft
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed executable$(RESET_COLOR)\n"

re: clean all
relib: fclean all

.PHONY: all clean fclean re relib
