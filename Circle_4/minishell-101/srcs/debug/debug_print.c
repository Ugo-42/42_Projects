/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:28:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 12:22:55 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug_includes/minishell_debug.h"

void	___debug___(const char *title, const char *value, uint32_t color)
{
	const uint32_t	darker_color = ft_darken_color(color, 25);

	if (DEBUG || ALWAYS_PRINT)
	{
		if (title)
			ft_printf("%F%s ", darker_color, title);
		if (value)
			ft_printf("%F[%F%s%F]\n", 0x424242, color, value, 0x424242);
		ft_print_nl_colored("────────────────", 0x424242);
	}
}
