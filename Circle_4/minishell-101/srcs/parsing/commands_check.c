/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:35:21 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:20:13 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SYNTAX_ERROR "syntax error near unexpected token `%s'"

static bool	error(char *msg, bool allocated_msg)
{
	ft_fprintf(2, PERR "%s\n", msg);
	if (allocated_msg)
		free(msg);
	return (false);
}

static bool	redirection(char **token, t_type *types, size_t i)
{
	if (!token[i + 1])
		return (error(ft_stringf(SYNTAX_ERROR, token[i]), true));
	else
	{
		if (is_operator(token[i + 1]) && types[i + 1] != FILENAME)
			return (error(ft_stringf(SYNTAX_ERROR, token[i + 1]), true));
	}
	return (true);
}

static bool	_pipe_(char **token, t_type *types, size_t i)
{
	if (!token[i + 1])
	{
		return (error(ft_stringf(SYNTAX_ERROR, token[i]), true));
	}
	if (token[i - 1] && (types[i - 1] == PIPE))
	{
		return (error(ft_stringf(SYNTAX_ERROR, token[i]), true));
	}
	return (true);
}

bool	commands_check(t_shell *shell, char **token)
{
	size_t	i;

	i = 0;
	if (shell->types[i] == PIPE)
		return (error(ft_stringf(SYNTAX_ERROR, token[i]), true));
	while (token[i])
	{
		if (shell->types[i] == REDIR_IN || shell->types[i] == REDIR_OUT
			|| shell->types[i] == REDIR_APPEND || shell->types[i] == HEREDOC)
		{
			if (!redirection(token, shell->types, i))
				return (false);
			i++;
		}
		if (token[i] && shell->types[i] == COMMAND)
			if (is_operator(token[i]))
				return (error(ft_stringf(SYNTAX_ERROR, token[i + 1]), true));
		if (token[i] && (shell->types[i] == PIPE))
			if (!_pipe_(token, shell->types, i))
				return (false);
		if (token[i])
			i++;
	}
	return (true);
}
