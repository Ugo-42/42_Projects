/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/20 13:49:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_2d(char **array, size_t nmemb)
{
	char	**copy;
	size_t	i;

	if (!array)
		return (NULL);
	copy = malloc((nmemb + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < nmemb)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			ft_free_2d_char_array(&copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
