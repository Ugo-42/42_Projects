/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:11:14 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/09 09:24:17 by lrieffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*flexistr2d_get(t_flexistr2d *arstr, int pos)
{
	if (!arstr)
		return (NULL);
	ft_normalize(&pos, 0, arstr->len);
	return (arstr->str[pos]);
}
