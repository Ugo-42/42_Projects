/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:35:05 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:15:58 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(t_shell *shell, char *path, char *cmd)
{
	if (!path && is_directory(cmd))
	{
		ft_fprintf(2, PERR "%s: Is a directory\n", cmd);
		free(path);
		ft_cexit(126, cleanup, shell);
	}
	else if (!path)
	{
		ft_fprintf(2, PERR "%s: command not found\n", cmd);
		ft_cexit(127, cleanup, shell);
	}
	else if (shell->env.total_bytes > ARG_MAX)
	{
		ft_fprintf(2, PERR "%s: Argument list too long\n", path);
		free(path);
		ft_cexit(126, cleanup, shell);
	}
	else
	{
		free(path);
		ft_cexit_error(1, "execve failed", cleanup, shell);
	}
}

void	exec_binary(t_shell *shell, char **cmd)
{
	char	*path;

	path = get_command_path(cmd[0], shell->env.envp, shell);
	if (!path || shell->env.size > ARG_MAX)
		exec_error(shell, path, cmd[0]);
	restore_signal();
	if (execve(path, cmd, shell->env.envp) == -1)
		exec_error(shell, path, cmd[0]);
}

void	exec_binary_fork(t_shell *shell, char **cmd)
{
	char	*path;
	pid_t	pid;

	path = get_command_path(cmd[0], shell->env.envp, shell);
	pid = fork();
	if (pid == -1)
		ft_cexit(1, cleanup, shell);
	if (pid == 0)
	{
		if (!path || shell->env.size > ARG_MAX)
			exec_error(shell, path, cmd[0]);
		restore_signal();
		if (execve(path, cmd, shell->env.envp) == -1)
			exec_error(shell, path, cmd[0]);
	}
	waitpid(pid, &shell->exit_code, 0);
	free(path);
	shell->exit_code = convert_exit_status(shell->exit_code);
}
