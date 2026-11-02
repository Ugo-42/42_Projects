/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:46:14 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/30 09:20:45 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*flexistr2d_pop(t_flexistr2d *arstr)
{
	char	*result;

	if (!arstr)
		return (NULL);
	result = ft_strdup(arstr->str[arstr->len - 1]);
	ft_free_null(&arstr->str[--arstr->len]);
	return (result);
}

char	*flexistr2d_npop(t_flexistr2d *arstr, int n)
{
	char	*result;
	size_t	i;

	if (!arstr)
		return (NULL);
	ft_normalize(&n, 0, arstr->len);
	result = ft_strdup(arstr->str[n]);
	ft_free_null(&arstr->str[n]);
	i = n;
	while (i < arstr->len)
	{
		arstr->str[i] = arstr->str[i + 1];
		i++;
	}
	arstr->str[arstr->len - 1] = NULL;
	arstr->len--;
	return (result);
}
