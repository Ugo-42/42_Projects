/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/04 10:31:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_recalloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*result;

	if (new_size == old_size)
		return (ptr);
	if (!ptr)
		return (ft_calloc(1, new_size));
	if (!new_size)
		return (free(ptr), NULL);
	result = malloc(new_size);
	if (!result)
		return (free(ptr), NULL);
	if (old_size > new_size)
		old_size = new_size;
	ft_memcpy(result, ptr, old_size);
	ft_bzero((unsigned char *)result + old_size, new_size - old_size);
	free(ptr);
	return (result);
}
