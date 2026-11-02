/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percentile_strnb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:54:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/20 13:48:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmp(const void *a, const void *b)
{
	return (ft_cmp_strnb(*(char **)a, *(char **)b));
}

static char	*ft_find_percentile(char **numbers, char **copy,
		size_t nmemb, size_t index)
{
	size_t	i;

	i = 0;
	while (i < nmemb)
	{
		if (ft_cmp_strnb(copy[index], numbers[i]) == 0)
		{
			ft_free_2d_char_array(&copy);
			return (numbers[i]);
		}
		i++;
	}
	ft_free_2d_char_array(&copy);
	ft_exit_error(1, "In 'ft_percentile_strnb': " BAD_BAD);
	return (NULL);
}

char	*ft_percentile_strnb(char **numbers, size_t nmemb, double percentile)
{
	char	**copy;
	size_t	index;

	if (!numbers || nmemb == 0 || percentile < 0 || percentile > 100)
		ft_exit_error(1, "In 'ft_percentile_strnb': " BAD_ARG);
	index = (size_t)((percentile / 100.0) * (nmemb - 1));
	if (!ft_is_sorted(numbers, nmemb, sizeof(char *), ft_cmp))
	{
		copy = ft_strdup_2d(numbers, nmemb);
		if (!copy)
			ft_exit_error(1, "In 'ft_percentile_strnb': " BAD_ALLOC);
		ft_qsort(copy, nmemb, sizeof(char *), ft_cmp);
		return (ft_find_percentile(numbers, copy, nmemb, index));
	}
	return (numbers[index]);
}
