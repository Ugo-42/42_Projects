/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:25:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/03 13:13:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_2d(size_t dim1, size_t dim2, size_t size)
{
	void	**array;
	size_t	i;

	array = ft_calloc(dim1, sizeof(void *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < dim1)
	{
		array[i] = ft_calloc(dim2, size);
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
