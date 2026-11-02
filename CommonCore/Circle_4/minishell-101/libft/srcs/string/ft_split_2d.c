/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:17:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/25 10:03:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_total_size(char **array, const char *set)
{
	size_t	total_size;
	size_t	i;
	size_t	j;

	i = 0;
	total_size = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (ft_is_in_set(array[i][j], set))
				total_size++;
			j++;
		}
		i++;
	}
	return (total_size);
}

static size_t	count_until_is_in_set(char **array, const char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (ft_is_in_set(array[i][j], set))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static void	split_and_store(char ***result, char **array, const char *set)
{
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (array[j])
	{
		size = count_until_is_in_set(array + j, set);
		result[i] = ft_strdup_2d(array + j, size);
		i++;
		j += size;
		if (array[j])
		{
			result[i] = malloc(2 * sizeof(char *));
			result[i][0] = ft_strdup(array[j]);
			result[i][1] = NULL;
			i++;
			j++;
		}
	}
	result[i] = NULL;
}

char	***ft_split_2d(char **array, const char *set)
{
	char	***result;
	size_t	total_size;

	total_size = count_total_size(array, set) * 2 + 1;
	result = malloc((total_size + 1) * sizeof(char **));
	if (!result)
		return (NULL);
	split_and_store(result, array, set);
	return (result);
}
