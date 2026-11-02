/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:18:02 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/22 14:49:19 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cd_err(t_shell *shell, const char *err_msg, bool chdir_err)
{
	if (chdir_err)
		ft_fprintf(2, PERR "cd: %s: %s\n", err_msg, strerror(errno));
	else
		ft_fprintf(2, PERR "cd: %s\n", err_msg);
	shell->exit_code = 1;
}

void	exec_cd(t_shell *shell, char **cmd)
{
	const char	*path = cmd[1];

	shell->exit_code = 0;
	if (!cmd[1])
	{
		path = get_env_var("HOME", shell->env.envp, shell);
		if (!path)
			print_cd_err(shell, "HOME no set", false);
		else if (chdir(path) < 0)
			print_cd_err(shell, path, true);
	}
	else if (!cmd[2])
	{
		if (chdir(path) < 0)
			print_cd_err(shell, path, true);
	}
	else
		print_cd_err(shell, "too many arguments", false);
}
