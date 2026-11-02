/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:18:10 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/24 14:41:27 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	double_envp_size(t_shell *shell)
{
	shell->env.envp = ft_realloc(
			shell->env.envp, sizeof(char *) * shell->env.size,
			sizeof(char *) * shell->env.size * 2);
	shell->env.size *= 2;
}

static bool	is_valid(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_is_alpha(cmd[i]) && cmd[i] != '_')
		return (false);
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
	{
		if (!ft_is_alnum(cmd[i]) && cmd[i] != '_')
			return (false);
		i++;
	}
	if (!cmd[i] || (cmd[i] && (cmd[i] != '=' && cmd[i] != '+' )))
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (true);
		return (false);
	}
	return (true);
}

static char	*replace_or_add(t_shell *shell, char *cmd)
{
	const char	*v_value;
	char		*v_name;
	char		*tmp;

	v_name = ft_strdup(cmd);
	if (ft_strchr(v_name, '=')[-1] == '+')
	{
		*ft_strchr(v_name, '+') = '\0';
		v_value = get_env_var(v_name, shell->env.envp, shell);
		if (!v_value)
			v_value = "";
		tmp = cmd;
		cmd = ft_stringf("%s=%s%s", v_name, v_value, ft_strchr(tmp, '=') + 1);
		free(tmp);
	}
	else if (ft_strchr(v_name, '=') != NULL)
		*ft_strchr(v_name, '=') = '\0';
	if (get_env_var(v_name, shell->env.envp, shell) != NULL)
		exec_unset(shell, (char *[]){"unset", v_name, NULL});
	free(v_name);
	return (cmd);
}

void	exec_export(t_shell *shell, char **cmd)
{
	int		i;

	shell->exit_code = 0;
	i = 1;
	while (cmd[i])
	{
		if (is_valid(cmd[i]))
		{
			cmd[i] = replace_or_add(shell, cmd[i]);
			if (shell->env.nb_env + 1 >= shell->env.size)
				double_envp_size(shell);
			shell->env.envp[shell->env.nb_env++] = ft_strdup(cmd[i]);
			shell->env.envp[shell->env.nb_env] = NULL;
			shell->env.total_bytes += ft_strlen(cmd[i]) + 1;
		}
		else if (ft_strchr(cmd[i], '=') != NULL)
		{
			shell->exit_code = 1;
			ft_fprintf(2, PERR "export: %s: not a valid identifier\n", cmd[i]);
		}
		i++;
	}
}
