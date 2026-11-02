/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_reverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:15:27 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:55:54 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_reverse(t_flexistr2d *arstr)
{
	int				i;
	t_flexistr2d	arstr2;

	if (!arstr)
		return ;
	if (flexistr2d_init(&arstr2, NULL, arstr->alloc_size) != 0)
		return ;
	i = arstr->len - 1;
	while (i >= 0)
	{
		if (arstr->str[i] != NULL)
			flexistr2d_append(&arstr2, flexistr2d_get(arstr, i));
		i--;
	}
	flexistr2d_dup(&arstr2, arstr);
	flexistr2d_close(&arstr2);
}
