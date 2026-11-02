/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:57:19 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 13:26:51 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_int(int signo)
{
	(void)signo;
	if (in_tty())
	{
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal(void)
{
	set_signal(SIGINT, sig_int);
	set_signal(SIGQUIT, SIG_IGN);
}
