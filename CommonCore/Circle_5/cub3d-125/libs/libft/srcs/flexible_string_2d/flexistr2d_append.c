/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:35:46 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:55:20 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_append(t_flexistr2d *arstr, char *to_add)
{
	if (!to_add || !arstr || !flexistr2d_need_realloc(arstr))
		return ;
	arstr->str[arstr->len] = ft_strdup(to_add);
	arstr->len++;
}

void	flexistr2d_fappend(t_flexistr2d *arstr, char *to_add)
{
	if (!to_add || !arstr || !flexistr2d_need_realloc(arstr))
		return ;
	arstr->str[arstr->len] = ft_strdup(to_add);
	free(to_add);
	arstr->len++;
}
