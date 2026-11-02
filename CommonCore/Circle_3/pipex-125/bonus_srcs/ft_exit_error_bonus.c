/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:44:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/03 15:20:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exit_error(int exit_code, char *infos)
{
	ft_fprintf(2, "%s: %s: %s\n", PROG_NAME, infos, strerror(errno));
	exit(exit_code);
}
