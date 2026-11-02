/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:54:44 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/07 09:54:46 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(int signal, void (*handler)(int))
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signal, &sa, NULL) == -1)
		perror(PERR "sigaction");
}
