/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:46:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/12 23:50:30 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal/mem_manager.h"

void	*mm_alloc(size_t size)
{
	t_mem_header	*header;

	header = malloc(sizeof(t_mem_header) + size);
	if (!header)
		return (NULL);
	header->size = size;
	if (!internal_manager(MM_ADD, header + 1))
		return (NULL);
	return (header + 1);
}
