/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:28:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 14:19:19 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug_includes/minishell_debug.h"

static void	print_type(t_type type, uint32_t color)
{
	if (type == COMMAND)
		ft_printf("%F%<s", color, 10, "COMMAND");
	else if (type == ARGUMENT)
		ft_printf("%F%<s", color, 10, "ARGUMENT");
	else if (type == REDIR_IN)
		ft_printf("%F%<s", color, 10, "REDIR_IN");
	else if (type == REDIR_OUT)
		ft_printf("%F%<s", color, 10, "REDIR_OUT");
	else if (type == REDIR_APPEND)
		ft_printf("%F%<s", color, 10, "REDIR_APPEND");
	else if (type == HEREDOC)
		ft_printf("%F%<s", color, 10, "HEREDOC");
	else if (type == FILENAME)
		ft_printf("%F%<s", color, 10, "FILENAME");
	else if (type == PIPE)
		ft_printf("%F%<s", color, 10, "PIPE");
	else
		ft_printf("%F%<s", color, 10, "UNKNOWN");
}

void	___debug_type___(const char *title, char **token, t_type *types,
		uint32_t color)
{
	const uint32_t	darker_color = ft_darken_color(color, 25);
	const uint32_t	brighter_color = ft_brighten_color(color, 25);
	const int		len = ft_strlen_2d(token);
	int				i;

	if (DEBUG || ALWAYS_PRINT)
	{
		if (title)
			ft_printf("%F%s\n", darker_color, title);
		i = 0;
		while (i < len)
		{
			ft_change_color(color);
			print_type(types[i], color);
			ft_printf("%F:: %F%s\n", darker_color, brighter_color, token[i++]);
		}
		ft_print_nl_colored("────────────────", 0x424242);
	}
}
