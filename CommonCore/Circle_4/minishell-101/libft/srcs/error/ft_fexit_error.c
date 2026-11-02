/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fexit_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:53:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"

void	ft_fexit_error(int exit_code, char *error_msg)
{
	if (FANCY == 1)
	{
		ft_putstr_fd(2, BOLD TOP_LOW_LINE RED "Error\n" RESET_COLOR);
		if (error_msg)
		{
			ft_fprintf(2, "%s\n", error_msg);
			free(error_msg);
		}
	}
	else
	{
		if (error_msg)
			free(error_msg);
		ft_putstrn_fd(2, "Error\n", 6);
	}
	exit(exit_code);
}
