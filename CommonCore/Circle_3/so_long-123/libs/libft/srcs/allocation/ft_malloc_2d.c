/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:25:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/03 13:11:34 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc_2d(size_t dim1, size_t dim2, size_t size)
{
	void	**array;
	size_t	i;

	if (!dim1 || !dim2 || !size)
		return (NULL);
	array = malloc(dim1 * sizeof(void *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < dim1)
	{
		array[i] = malloc(dim2 * size);
		if (!array[i])
		{
			while (i > 0)
				free(array[--i]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}
