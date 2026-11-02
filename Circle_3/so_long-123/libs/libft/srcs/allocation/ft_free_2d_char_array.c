/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_char_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:15:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/20 13:49:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_2d_char_array(char ***array)
{
	size_t	i;

	if (array && *array)
	{
		i = 0;
		while ((*array)[i])
		{
			free((*array)[i]);
			(*array)[i] = NULL;
			i++;
		}
		free(*array);
		*array = NULL;
	}
	return (NULL);
}
