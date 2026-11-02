/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:07:07 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 16:13:00 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_pipe_nb(t_shell *shell)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (shell->token && shell->token[i])
	{
		if (shell->types[i] == PIPE)
			count++;
		i++;
	}
	return (count);
}

static size_t	get_arg_nb(t_shell *shell, size_t *j)
{
	size_t		count;

	count = 0;
	if (!shell->token)
		return (0);
	while (shell->token[*j] && shell->types[*j] != PIPE)
	{
		if (shell->types[*j] == ARGUMENT || shell->types[*j] == COMMAND)
			count++;
		*j += 1;
	}
	if (shell->token[*j] && shell->types[*j] == PIPE)
		*j += 1;
	return (count);
}

static void	copy_arg(t_shell *shell, t_commands *cmd, size_t *i)
{
	size_t		j;

	j = 0;
	while (shell->token[*i] && shell->types[*i] != PIPE)
	{
		if (shell->types[*i] == ARGUMENT || shell->types[*i] == COMMAND)
		{
			cmd->cmd[j] = ft_strdup(shell->token[*i]);
			if (!cmd->cmd[j])
			{
				while (--j > 0)
					ft_free_null(shell->commands->cmd[j]);
				ft_cexit_error(1, INTERR "allocation failed", cleanup, shell);
			}
			j++;
		}
		*i += 1;
	}
	cmd->cmd[j] = NULL;
	if (shell->token[*i] && shell->types[*i] == PIPE)
		*i += 1;
}

static void	create_commands(t_shell *shell)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < shell->commands->nb_cmd)
	{
		shell->commands[i].cmd
			= ft_calloc((get_arg_nb(shell, &j) + 1), sizeof (char *));
		if (!shell->commands->cmd)
		{
			while (--i > 0)
				ft_free_null(shell->commands[i].cmd);
			ft_cexit_error(1, INTERR "allocation failed", cleanup, shell);
		}
		i++;
	}
	shell->commands[i].cmd = NULL;
}

void	split_commands(t_shell *shell)
{
	size_t	nb_cmd;
	size_t	i;
	size_t	j;

	if (!shell->token)
		return ;
	nb_cmd = get_pipe_nb(shell) + 1;
	shell->commands = ft_calloc((nb_cmd + 1), sizeof(t_commands));
	if (!shell->commands)
		ft_cexit_error(1, INTERR "allocation failed", cleanup, shell);
	shell->commands->nb_cmd = nb_cmd;
	i = 0;
	create_commands(shell);
	i = 0;
	j = 0;
	while (i < nb_cmd)
	{
		copy_arg(shell, &shell->commands[i], &j);
		i++;
	}
}
