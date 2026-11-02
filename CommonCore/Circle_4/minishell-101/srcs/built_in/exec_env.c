/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:17:46 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/22 15:28:25 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_shell *shell, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		ft_putstr_nl_fd(2, PERR "env: too many arguments");
		shell->exit_code = 1;
	}
	else
	{
		i = 0;
		while (shell->env.envp[i])
			ft_putstr_nl(shell->env.envp[i++]);
		shell->exit_code = 0;
	}
}
