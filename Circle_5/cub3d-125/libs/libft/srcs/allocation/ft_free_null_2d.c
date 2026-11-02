/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:15:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/20 13:56:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes the ADDRESS of of 2d pointer, frees each n pointer and NULLs them */
/* Then frees and NULLs the base pointer */

void	*ft_free_null_2d(void *array_address, size_t n)
{
	void	***array;
	size_t	i;

	if (!array_address)
		return (NULL);
	array = (void ***)array_address;
	if (!*array)
		return (NULL);
	i = 0;
	while (i < n)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
	return (NULL);
}
