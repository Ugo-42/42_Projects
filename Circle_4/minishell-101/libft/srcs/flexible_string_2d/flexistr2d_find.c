/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:57:49 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:55:27 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	flexistr2d_find(t_flexistr2d *arstr, char *pattern)
{
	int	i;

	if (!arstr || !pattern)
		return (-1);
	i = -1;
	while (arstr->str[++i])
	{
		if (!ft_strcmp(arstr->str[i], pattern))
			return (i);
	}
	return (-1);
}

int	flexistr2d_count(t_flexistr2d *arstr, char *pattern)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (!arstr || !pattern)
		return (count);
	while (arstr->str[++i])
	{
		if (!ft_strcmp(arstr->str[i], pattern))
			count++;
	}
	return (count);
}

void	flexistr2d_rempattern(t_flexistr2d *arstr, char *pattern)
{
	while (flexistr2d_find(arstr, pattern) != -1)
		flexistr2d_remove(arstr, flexistr2d_find(arstr, pattern));
}

int	flexistr2d_ffind(t_flexistr2d *arstr, char *pattern)
{
	int	i;

	if (!arstr || !pattern)
		return (free(pattern), -1);
	i = -1;
	while (arstr->str[++i])
	{
		if (!ft_strcmp(arstr->str[i], pattern))
			return (free(pattern), i);
	}
	return (free(pattern), -1);
}
