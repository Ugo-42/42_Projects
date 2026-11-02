/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:12 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/25 15:14:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug_includes/minishell_debug.h"

void	___debug_commands___(t_commands *cmds, uint32_t color)
{
	size_t	i;
	char	*cmd_nb;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i].cmd)
	{
		cmd_nb = ft_stringf("command[%d]:", i);
		___debug_2d___(cmd_nb, cmds[i++].cmd, color);
		free(cmd_nb);
	}
}
