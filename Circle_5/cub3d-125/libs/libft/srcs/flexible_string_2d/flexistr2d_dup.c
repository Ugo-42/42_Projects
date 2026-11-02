/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:23:39 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:57:22 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_dup(t_flexistr2d *src, t_flexistr2d *dest)
{
	size_t	i;

	if (!src)
		return ;
	if (dest)
		flexistr2d_close(dest);
	if (flexistr2d_init(dest, NULL, src->len + 1) != 0)
		return ;
	i = 0;
	while (i < src->len)
	{
		flexistr2d_append(dest, flexistr2d_get(src, i));
		i++;
	}
}
