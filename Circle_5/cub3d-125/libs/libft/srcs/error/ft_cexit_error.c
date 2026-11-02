/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cexit_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/24 11:12:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"

void	ft_cexit_error(int exit_code, char *error_msg, void (*clean_ft)(void *),
		void *clean_arg)
{
	ft_putstr_fd(2, BOLD TOP_LOW_LINE RED "Error\n" RESET_COLOR);
	if (error_msg)
	{
		ft_fprintf(2, "%s\n", error_msg);
	}
	if (clean_ft)
		clean_ft(clean_arg);
	exit(exit_code);
}
