/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:28:37 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/28 14:24:22 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SHLVLTOOHIGH "warning: shell level (%d) too high, resetting to 1\n"

static void	set_shlvl(t_shell *shell)
{
	const char	*shlvl = get_env_var("SHLVL", shell->env.envp, shell);
	char		*new_shlvl;
	int			lvl;

	if (!shlvl)
		exec_export(shell, (char *[]){"export", "SHLVL=1", NULL});
	else
	{
		lvl = ft_atoi(shlvl) + 1;
		new_shlvl = ft_stringf("SHLVL=%d", lvl);
		if (lvl > 999 || lvl < 1)
		{
			if (lvl > 999)
				ft_fprintf(2, PERR SHLVLTOOHIGH, lvl);
			new_shlvl = ft_strdup("SHLVL=1");
		}
		exec_export(shell, (char *[]){"export", new_shlvl, NULL});
		free(new_shlvl);
	}
}

static size_t	get_envp_tsize(t_shell *shell)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (shell->env.envp[i])
		res += ft_strlen(shell->env.envp[i++]) + 1;
	return (res);
}

static void	copy_envp(t_shell *shell, char **envp)
{
	int		i;

	shell->env.nb_env = ft_strlen_2d(envp);
	shell->env.size = ft_next_power_of_2(shell->env.nb_env * 2);
	shell->env.envp = ft_calloc((shell->env.size + 1), sizeof(char *));
	if (!shell->env.envp)
		return ;
	i = 0;
	while (envp[i])
	{
		shell->env.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->env.envp[i] = NULL;
	shell->env.total_bytes = get_envp_tsize(shell);
}

void	init_shell(t_shell *shell, char **envp)
{
	ft_bzero(shell, sizeof(t_shell));
	copy_envp(shell, envp);
	set_shlvl(shell);
}
