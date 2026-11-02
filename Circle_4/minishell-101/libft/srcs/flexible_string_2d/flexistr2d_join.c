/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:23:55 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:55:34 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_joinflex(t_flexistr2d *arstr1, t_flexistr2d *arstr2)
{
	if (arstr1 == NULL || arstr2 == NULL)
		return ;
	while (arstr2->len > 0)
	{
		flexistr2d_fappend(arstr1, flexistr2d_npop(arstr2, 0));
	}
	flexistr2d_close(arstr2);
}

void	flexistr2d_joinstr(t_flexistr2d *arstr, char **str)
{
	if (arstr == NULL || str == NULL)
		return ;
	while (*str != NULL)
	{
		flexistr2d_append(arstr, *str);
		str++;
	}
}

void	flexistr2d_fjoinstr(t_flexistr2d *arstr, char **str)
{
	int	i;

	if (arstr == NULL || str == NULL)
		return (ft_free_2d_char_array(&str), (void)0x0);
	i = 0;
	while (str[i])
		flexistr2d_append(arstr, str[i++]);
	ft_free_2d_char_array(&str);
}
