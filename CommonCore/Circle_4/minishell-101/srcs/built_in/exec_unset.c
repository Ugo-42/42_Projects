/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:18:15 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/22 13:19:25 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	halve_envp_size(t_shell *shell)
{
	shell->env.envp = ft_realloc(
			shell->env.envp, sizeof(char *) * shell->env.size,
			sizeof(char *) * (shell->env.size / 2));
	shell->env.size /= 2;
}

static void	unset_var(t_shell *shell, char *var)
{
	const size_t	var_len = ft_strlen(var);
	char			**env;
	int				i;

	i = 0;
	env = shell->env.envp;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
		{
			shell->env.total_bytes -= ft_strlen(env[i]) + 1;
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[--shell->env.nb_env] = NULL;
			return ;
		}
		i++;
	}
}

void	exec_unset(t_shell *shell, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		unset_var(shell, cmd[i++]);
		if (shell->env.nb_env * 4 <= shell->env.size)
			halve_envp_size(shell);
	}
	shell->exit_code = 0;
}
