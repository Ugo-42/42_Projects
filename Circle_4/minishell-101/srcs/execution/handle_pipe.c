/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:04:25 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:10:12 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_io(t_shell *shell, size_t i)
{
	if (i > 0)
	{
		if (dup2(shell->pipe_fd[i - 1][0], shell->fd.in) == -1)
			ft_cexit_error(1, INTERR "dup2 failed", cleanup, shell);
	}
	if (i < shell->commands->nb_cmd - 1)
	{
		if (dup2(shell->pipe_fd[i][1], shell->fd.out) == -1)
			ft_cexit_error(1, INTERR "dup2 failed", cleanup, shell);
	}
}

static void	child_process_pipe(t_shell *shell, size_t i)
{
	if (!handle_redirections(shell, &shell->redirections[i]))
	{
		close_pipes(&shell->pipe_fd, shell->commands->nb_cmd - 1);
		ft_cexit(1, cleanup, shell);
	}
	if (!shell->pipe_fd)
		ft_cexit(1, cleanup, shell);
	set_pipe_io(shell, i);
	close_pipes(&shell->pipe_fd, shell->commands->nb_cmd - 1);
	if (shell->commands[i].cmd[0])
	{
		command_executor(shell, shell->commands[i].cmd);
	}
	ft_cexit(shell->exit_code, cleanup, shell);
}

static pid_t	execute_pipe(t_shell *shell, size_t i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_cexit_error(1, INTERR "Fork failed", cleanup, shell);
	if (pid == 0)
		child_process_pipe(shell, i);
	shell->curr_heredoc += get_heredoc_number(shell->redirections[i].redi);
	return (pid);
}

void	handle_pipe(t_shell *shell)
{
	int		wstatus;
	pid_t	last_pid;
	pid_t	pid;
	size_t	i;

	i = 0;
	last_pid = -1;
	open_pipes(&shell->pipe_fd, shell->commands->nb_cmd - 1);
	while (i < shell->commands->nb_cmd)
	{
		pid = execute_pipe(shell, i);
		if (i == shell->commands->nb_cmd - 1)
			last_pid = pid;
		i++;
	}
	close_pipes(&shell->pipe_fd, shell->commands->nb_cmd - 1);
	i = 0;
	while (i < shell->commands->nb_cmd)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == last_pid)
			shell->exit_code = convert_exit_status(wstatus);
		i++;
	}
	free_pipes(&shell->pipe_fd, shell->commands->nb_cmd - 1);
}
