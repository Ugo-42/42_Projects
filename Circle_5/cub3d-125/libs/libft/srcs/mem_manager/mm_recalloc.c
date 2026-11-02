/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_recalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:53:11 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/13 12:04:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal/mem_manager.h"
#include "libft.h"

void	*mm_recalloc(void *ptr, size_t new_size)
{
	size_t			old_size;
	size_t			size;
	void			*new_ptr;

	if (!ptr)
		return (mm_calloc(new_size));
	old_size = ((t_mem_header *)ptr - 1)->size;
	if (old_size == new_size)
		return (ptr);
	if (!new_size)
		return (mm_free(ptr), NULL);
	new_ptr = mm_alloc(new_size);
	if (!new_ptr)
		return (mm_free(ptr), NULL);
	size = ft_iternary(old_size < new_size, old_size, new_size);
	ft_memcpy(new_ptr, ptr, size);
	ft_bzero((t_byte *)new_ptr + old_size, new_size - old_size);
	mm_free(ptr);
	return (new_ptr);
}
