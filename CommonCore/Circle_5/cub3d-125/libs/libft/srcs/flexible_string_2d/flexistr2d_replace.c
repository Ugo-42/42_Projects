/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:38:41 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/30 10:27:09 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_replace(t_flexistr2d *arstr, char *replace, int n)
{
	if (!arstr->str)
		return ;
	ft_normalize(&n, 0, arstr->len);
	flexistr2d_remove(arstr, n);
	flexistr2d_add(arstr, replace, n);
}
