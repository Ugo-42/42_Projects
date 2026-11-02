/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:06:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/05 15:25:31 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_redi_cmd(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->redirections)
	{
		while (i < shell->commands->nb_cmd)
		{
			if (shell->redirections[i].redi)
				ft_free_2d_char_array(&shell->redirections[i].redi);
			if (shell->redirections[i].type)
				ft_free_null(&shell->redirections[i++].type);
		}
		ft_free_null(&shell->redirections);
	}
	i = 0;
	if (shell->commands)
	{
		if (shell->commands->cmd)
			while (i < shell->commands->nb_cmd)
				ft_free_2d_char_array(&shell->commands[i++].cmd);
		ft_free_null(&shell->commands);
	}
}

static void	clean_pipe(t_shell *shell)
{
	size_t	i;

	if (shell->pipe_fd && shell->commands)
	{
		i = 0;
		while (i < shell->commands->nb_cmd - 1)
			ft_free_null(&shell->pipe_fd[i++]);
		ft_free_null(&shell->pipe_fd);
	}
}

static void	clean_heredoc(t_shell *shell)
{
	size_t	i;
	size_t	heredoc_number;

	if (shell->heredocs)
	{
		heredoc_number = get_heredoc_number(shell->token);
		i = 0;
		while (i < heredoc_number)
		{
			ft_free_null(&shell->heredocs[i].delimiter);
			ft_close_null(&shell->heredocs[i++].fd);
		}
		ft_free_null(&shell->heredocs);
	}
}

void	cleanup(void *param)
{
	t_shell	*shell;

	shell = param;
	clean_pipe(shell);
	clean_heredoc(shell);
	ft_free_null(&shell->input);
	ft_free_null(&shell->types);
	ft_free_2d_char_array(&shell->env.envp);
	ft_free_2d_char_array(&shell->token);
	clean_redi_cmd(shell);
	ft_close_null(&shell->fd.in);
	ft_close_null(&shell->fd.out);
	ft_close_null(&shell->fd.std_in);
	ft_close_null(&shell->fd.std_out);
	close(STDERR_FILENO);
}
