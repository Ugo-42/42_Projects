/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:33:53 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 14:45:15 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*const_itoa(int n)
{
	static char		result[12];
	unsigned int	nb;
	size_t			i;

	nb = ft_iternary((n < 0), -n, n);
	result[11] = '\0';
	i = 10;
	while (nb > 0 || i == 10)
	{
		result[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i--] = '-';
	return (&result[i + 1]);
}

const char	*get_env_var(const char *varname, char **envp, t_shell *shell)
{
	size_t	len;
	int		i;

	if (!envp || !varname)
		return (NULL);
	if (*varname == '?')
		return (const_itoa(shell->exit_code));
	len = ft_strlen(varname);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varname, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
