/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_tty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:48:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 09:48:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_tty(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (true);
	return (false);
}
