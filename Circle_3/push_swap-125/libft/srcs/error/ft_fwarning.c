/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:53:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"

void	ft_fwarning(char *error_msg)
{
	ft_fprintf(2, BOLD TOP_LOW_LINE YELLOW "Warning\n" RESET_COLOR);
	if (error_msg)
	{
		ft_fprintf(2, "%s\n", error_msg);
		free(error_msg);
	}
}
