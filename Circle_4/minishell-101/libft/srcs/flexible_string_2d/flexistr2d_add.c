/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:48:21 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 10:55:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_add(t_flexistr2d *arstr, char *to_add, int n)
{
	size_t	i;

	if (!to_add || !arstr || !flexistr2d_need_realloc(arstr))
		return ;
	ft_normalize(&n, 0, arstr->len);
	arstr->len++;
	i = arstr->len - 1;
	while (i > (size_t)n)
	{
		ft_free_null(&arstr->str[i]);
		arstr->str[i] = ft_strdup(arstr->str[i - 1]);
		i--;
	}
	ft_free_null(&arstr->str[n]);
	arstr->str[n] = ft_strdup(to_add);
}

void	flexistr2d_fadd(t_flexistr2d *arstr, char *to_add, int n)
{
	size_t	i;

	if (!to_add || !arstr || !flexistr2d_need_realloc(arstr))
		return ;
	ft_normalize(&n, 0, arstr->len);
	arstr->len++;
	i = arstr->len - 1;
	while (i > (size_t)n)
	{
		ft_free_null(&arstr->str[i]);
		arstr->str[i] = ft_strdup(arstr->str[i - 1]);
		i--;
	}
	ft_free_null(&arstr->str[n]);
	arstr->str[n] = ft_strdup(to_add);
	ft_free_null(&to_add);
}
