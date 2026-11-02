/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:47:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 16:13:31 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_left_children(t_shell *shell)
{
	int		wstatus;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == -1)
		{
			if (errno == ECHILD)
				break ;
			if (errno == EINTR)
				continue ;
			else
				perror(PERR "waitpid");
		}
		else
			shell->exit_code = convert_exit_status(wstatus);
	}
}

void	execute_command(t_shell *shell, char **cmd)
{
	if (shell->commands->nb_cmd == 1)
	{
		if (!handle_redirections(shell, &shell->redirections[0]))
			return ;
		command_executor(shell, cmd);
	}
	else
	{
		handle_pipe(shell);
	}
	wait_left_children(shell);
}
