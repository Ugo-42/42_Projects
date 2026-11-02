/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:48:21 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:55:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	flexistr2d_need_realloc(t_flexistr2d *arstr)
{
	if (!arstr->alloc_size || !arstr->str)
		return (false);
	if (arstr->len + 1 >= arstr->alloc_size)
	{
		arstr->str = ft_recalloc(arstr->str, arstr->alloc_size * sizeof(char *),
				arstr->alloc_size * 2 * sizeof(char *));
		if (!arstr->str)
			return (false);
		arstr->alloc_size *= 2;
	}
	return (true);
}
