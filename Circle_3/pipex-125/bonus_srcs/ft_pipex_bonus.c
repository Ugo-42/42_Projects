/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:15:46 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 12:01:22 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_wait_for_children(size_t nb_cmd)
{
	size_t	i;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

static void	ft_free_resources(int **pipes, t_io_fd files, size_t nb_cmd,
		int exit_code)
{
	ft_close_pipes(&pipes, nb_cmd - 1);
	ft_wait_for_children(nb_cmd - 1);
	close(files.input);
	close(files.output);
	ft_free_pipes(&pipes, nb_cmd - 1);
	if (exit_code)
	{
		exit(exit_code);
	}
}

static void	ft_set_redirections(int **pipes, t_io_fd files, size_t i,
		size_t nb_cmd)
{
	if (i == 0)
		dup2(files.input, STDIN_FILENO);
	else
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i == nb_cmd - 1)
		dup2(files.output, STDOUT_FILENO);
	else
		dup2(pipes[i][1], STDOUT_FILENO);
	ft_close_pipes(&pipes, nb_cmd - 1);
	close(files.input);
	close(files.output);
}

void	ft_pipex(size_t nb_cmd, size_t cmd_start, char **argv, char **envp)
{
	int		exit_code;
	int		**pipes;
	pid_t	pid;
	size_t	i;
	t_io_fd	files;

	ft_open_files(&files, argv[1], argv[cmd_start + nb_cmd]);
	ft_open_pipes(&pipes, nb_cmd - 1);
	i = 0;
	while (i < nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_exit_error(1, "fork");
		else if (pid == 0)
		{
			ft_set_redirections(pipes, files, i, nb_cmd);
			exit_code = ft_execute_command(argv[cmd_start + i], envp);
			if (exit_code)
				ft_free_resources(pipes, files, nb_cmd, exit_code);
		}
		i++;
	}
	ft_free_resources(pipes, files, nb_cmd, 0);
}
