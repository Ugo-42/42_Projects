/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:18:20 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/29 10:07:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LONG_MAX_STR "9223372036854775807"
#define LONG_MIN_STR "-9223372036854775808"

static bool	is_numeric_nb(char *number)
{
	size_t	i;

	i = 0;
	if (number[i] == '-' || number[i] == '+')
		i++;
	if (!ft_is_digit(number[i]))
		return (false);
	while (ft_is_digit(number[i]))
		i++;
	return (number[i] == '\0');
}

static bool	is_within_long_bounds(char *number)
{
	return (ft_cmp_strnb(number, LONG_MAX_STR) <= 0
		&& ft_cmp_strnb(number, LONG_MIN_STR) >= 0);
}

static void	clean_exit(t_shell *shell, int exit_code)
{
	cleanup(shell);
	exit(exit_code);
}

void	exec_exit(t_shell *shell, char **cmd)
{
	char	*err_msg;
	int		exit_code;

	ft_putstr("exit\n");
	if (!cmd[1])
		clean_exit(shell, 0);
	if (cmd[2])
	{
		ft_putstr_nl_fd(2, PERR "exit: too many arguments");
		ft_cexit(1, cleanup, shell);
	}
	if (!is_numeric_nb(cmd[1]) || !is_within_long_bounds(cmd[1]))
	{
		err_msg = ft_stringf(PERR "exit: %s: numeric argument "
				"required\n", cmd[1]);
		ft_putstr_fd(2, err_msg);
		free(err_msg);
		clean_exit(shell, 2);
	}
	exit_code = ft_atoi(cmd[1]);
	clean_exit(shell, exit_code);
}
