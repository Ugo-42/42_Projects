/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:46:43 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:26:05 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "debug_includes/minishell_debug.h"

static void	assign_heredoc(t_shell *shell, char **token, t_assign_type *t)
{
	shell->types[t->i] = HEREDOC;
	if (!token[t->i + 1])
		return ;
	shell->heredocs[t->j].expansion = true;
	if (token[t->i + 1][ft_strcspn(token[t->i + 1], "\"'")] == '\0')
		shell->heredocs[t->j].delimiter = ft_strdup(token[t->i + 1]);
	else
	{
		shell->heredocs[t->j].expansion = false;
		shell->heredocs[t->j].delimiter = strdup_reject(token[t->i + 1], "'\"");
	}
	t->j += 1;
}

static bool	assign_redirection(char **token, t_shell *shell, t_assign_type *t)
{
	if (is_redirection(token[t->i]))
	{
		if (ft_strcmp(token[t->i], "<") == 0)
			shell->types[t->i] = REDIR_IN;
		if (ft_strcmp(token[t->i], ">") == 0)
			shell->types[t->i] = REDIR_OUT;
		if (ft_strcmp(token[t->i], "<<") == 0)
			assign_heredoc(shell, token, t);
		if (ft_strcmp(token[t->i], ">>") == 0)
			shell->types[t->i] = REDIR_APPEND;
		if (token[t->i + 1])
		{
			if (!is_operator(token[t->i + 1]))
				shell->types[t->i + 1] = FILENAME;
			else
				shell->types[t->i + 1] = -1;
			t->i += 2;
		}
		else
			t->i += 1;
		return (true);
	}
	return (false);
}

static void	type_assignment(t_shell *shell, char **token, t_assign_type *t)
{
	while (token[t->i])
	{
		if (ft_strcmp(token[t->i], "|") == 0
			|| ft_strcmp(token[t->i], "||") == 0)
		{
			shell->types[t->i] = PIPE;
			t->is_command = false;
		}
		else if (assign_redirection(token, shell, t))
			continue ;
		else if (t->is_command == false)
		{
			shell->types[t->i] = COMMAND;
			t->is_command = true;
		}
		else
			shell->types[t->i] = ARGUMENT;
		t->i++;
	}
}

void	assign_types(t_shell *shell, char **token)
{
	t_assign_type	t;

	shell->types = ft_calloc(sizeof(t_type), shell->nb_tokens + 1);
	if (!shell->types)
		ft_cexit_error(1, PERR BAD_ALLOC, cleanup, shell);
	create_heredoc(shell);
	t = (t_assign_type){0, 0, false};
	type_assignment(shell, token, &t);
}
