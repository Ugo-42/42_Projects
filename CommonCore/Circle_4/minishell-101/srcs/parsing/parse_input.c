/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:22:56 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:36:04 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug_includes/minishell_debug.h"

static void	split_token(t_shell *shell)
{
	if (!*shell->input)
		return ;
	if (shell->token)
	{
		ft_free_2d_char_array(&shell->token);
		shell->token = NULL;
	}
	___debug___("Unformated:", shell->input, TURQUOISE);
	shell->input = separate_operators(shell->input);
	___debug___("Separated op:", shell->input, BRICK_RED);
	shell->token = ft_split_quoted(shell->input);
	if (!shell->token)
	{
		check_input_error(shell);
		shell->exit_code = 1;
	}
}

static void	expand_token(t_shell *shell)
{
	___debug_2d___("Split:", shell->token, OLIVE_GREEN);
	shell->nb_tokens = ft_count_words_quoted(shell->input);
	assign_types(shell, shell->token);
	___debug_type___("Tokens:", shell->token, shell->types, BLUE);
	expand_tokens(shell, shell->token);
	___debug_type___("Expended Tok:", shell->token, shell->types, PURPLE);
}

static void	split_pipe(t_shell *shell)
{
	split_commands(shell);
	___debug_commands___(shell->commands, ORANGE);
	split_redirections(shell);
	___debug_redirections___(shell->redirections, YELLOW);
}

void	parse_input(t_shell *shell)
{
	split_token(shell);
	if (!shell->token)
		return ;
	expand_token(shell);
	split_pipe(shell);
	if (!commands_check(shell, shell->token))
	{
		input_cleanup(shell);
		return ;
	}
	heredoc_signal();
	handle_heredoc(shell);
	if (!BLOCK_COMMANDS && isatty(STDIN_FILENO))
		execute_command(shell, shell->commands[0].cmd);
	handle_signal();
	input_cleanup(shell);
}
