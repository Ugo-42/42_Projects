/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/22 15:27:34 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_new_line(char *av1)
{
	int		i;

	if (!av1)
		return (false);
	i = 0;
	if (av1[i++] != '-')
		return (false);
	while (av1[i])
	{
		if (av1[i++] != 'n')
			return (false);
	}
	return (true);
}

static bool	werr(t_shell *shell, ssize_t n)
{
	if (n == -1)
	{
		perror(PERR "echo: write error");
		shell->exit_code = 1;
		return (true);
	}
	return (false);
}

void	exec_echo(t_shell *shell, char **cmd)
{
	bool	new_line;
	int		i;

	shell->exit_code = 0;
	i = 1;
	while (is_new_line(cmd[i]))
		i++;
	new_line = (i == 1);
	while (cmd[i])
	{
		if (werr(shell, ft_putstr(cmd[i])))
			return ;
		if (cmd[i + 1] && werr(shell, ft_putchar(' ')))
			return ;
		i++;
	}
	if (new_line)
	{
		if (werr(shell, ft_putchar('\n')))
			return ;
	}
}
