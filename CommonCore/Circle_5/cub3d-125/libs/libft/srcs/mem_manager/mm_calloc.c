/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/13 00:19:39 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*mm_calloc(size_t size)
{
	void	*ptr;

	ptr = mm_alloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	return (ptr);
}
