/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:12 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/28 12:46:56 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug_includes/minishell_debug.h"

void	___debug_redirections___(t_redirec *redirections, uint32_t color)
{
	size_t	i;
	char	*redir_nb;

	if (!redirections || redirections->nb_redi <= 0)
		return ;
	i = 0;
	while (redirections[i].redi)
	{
		redir_nb = ft_stringf("redirection[%d]:", i);
		___debug_type___(redir_nb, redirections[i].redi,
			redirections[i].type, color);
		free(redir_nb);
		i++;
	}
}
