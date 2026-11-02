/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:39:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/25 11:35:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug_includes/minishell_debug.h"

static void	print_2d(char **array, uint32_t color)
{
	if (!array)
		return ;
	while (*array)
		ft_printf("%F[%F%s%F] ", 0x424242, color, *array++, 0x424242);
}

void	___debug_2d___(const char *title, char **array, uint32_t color)
{
	const uint32_t	darker_color = ft_darken_color(color, 25);

	if (DEBUG || ALWAYS_PRINT)
	{
		if (title)
			ft_printf("%F%s ", darker_color, title);
		print_2d(array, color);
		ft_print_nl_colored("\n────────────────", 0x424242);
	}
}
