/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:44:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/02 15:04:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit_error(int exit_code, char *infos)
{
	ft_fprintf(2, "%s: %s: %s\n", PROG_NAME, infos, strerror(errno));
	exit(exit_code);
}
