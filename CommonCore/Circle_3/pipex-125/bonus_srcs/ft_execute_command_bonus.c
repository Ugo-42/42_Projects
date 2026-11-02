/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:44:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 13:02:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split_quoted(cmd);
	if (!args)
	{
		ft_exit_error(1, "split");
		return (1);
	}
	cmd_path = ft_get_command_path(args[0], envp);
	if (!cmd_path)
	{
		ft_fprintf(2, "%s: command not found: %s\n", PROG_NAME, args[0]);
		ft_free_2d_array(&args);
		return (127);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		ft_fprintf(2, "%s: execution failed: %s\n", PROG_NAME, args[0]);
		ft_free_2d_array(&args);
		free(cmd_path);
		return (1);
	}
	return (0);
}
