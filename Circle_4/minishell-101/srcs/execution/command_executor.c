/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:40:42 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 14:15:35 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_executor(t_shell *shell, char **cmd)
{
	size_t					i;
	static const t_command	commands[] = {
	{"export", exec_export}, {"cd", exec_cd},
	{"unset", exec_unset}, {"env", exec_env},
	{"exit", exec_exit}, {"echo", exec_echo},
	{"pwd", exec_pwd}};

	i = 0;
	if (cmd && *cmd && **cmd)
	{
		while (i < 7)
		{
			if (cmd && ft_strcmp(cmd[0], commands[i].name) == 0)
			{
				commands[i].func(shell, cmd);
				return ;
			}
			i++;
		}
		if (shell->commands->nb_cmd == 1)
			exec_binary_fork(shell, cmd);
		else
			exec_binary(shell, cmd);
	}
}
