/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:18:06 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/22 15:28:59 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_shell *shell, char **cmd)
{
	char	*path;

	(void)cmd;
	path = getcwd(NULL, 0);
	if (!path)
	{
		shell->exit_code = 1;
		perror("pwd: error retrieving current directory: getcwd");
	}
	else
	{
		shell->exit_code = 0;
		ft_putstr_nl(path);
		free(path);
	}
}
