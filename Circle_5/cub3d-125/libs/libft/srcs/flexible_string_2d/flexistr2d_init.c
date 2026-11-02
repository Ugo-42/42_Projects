/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:10:39 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 12:14:04 by lrieffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	flexistr2d_init(t_flexistr2d *arstr, char **base, size_t initial_size)
{
	if (initial_size == 0 && !base)
		return (-1);
	else if (initial_size == 0 && base)
		initial_size = ft_strlen_2d(base) + 1;
	if (base)
	{
		arstr->len = ft_strlen_2d(base);
		arstr->str = ft_strdup_2d(base, arstr->len);
		arstr->str = ft_recalloc(arstr->str, arstr->len * sizeof(char *),
				(initial_size + 1) * sizeof(char *));
		arstr->alloc_size = initial_size;
	}
	else
	{
		arstr->len = 0;
		arstr->str = ft_calloc(sizeof(char *), initial_size + 1);
		arstr->alloc_size = initial_size;
	}
	if (!arstr->str)
	{
		return (-1);
	}
	return (0);
}

int	flexistr2d_finit(t_flexistr2d *arstr, char **base, size_t initial_size)
{
	if (initial_size == 0 && !base)
		return (-1);
	else if (initial_size == 0 && base)
		initial_size = ft_strlen_2d(base) + 1;
	if (base)
	{
		arstr->len = ft_strlen_2d(base);
		arstr->str = ft_strdup_2d(base, arstr->len);
		arstr->str = ft_recalloc(arstr->str, arstr->len * sizeof(char *),
				(initial_size + 1) * sizeof(char *));
		arstr->alloc_size = initial_size;
	}
	else
	{
		arstr->len = 0;
		arstr->str = ft_calloc(sizeof(char *), initial_size + 1);
		arstr->alloc_size = initial_size;
	}
	if (!arstr->str)
	{
		ft_free_2d_char_array(&base);
		return (-1);
	}
	ft_free_2d_char_array(&base);
	return (0);
}
