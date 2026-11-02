/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:49:46 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 09:20:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_here(int signo)
{
	(void)signo;
	if (in_tty())
	{
		ft_putchar('\n');
		close(STDIN_FILENO);
	}
}

void	heredoc_signal(void)
{
	set_signal(SIGINT, sigint_here);
}
