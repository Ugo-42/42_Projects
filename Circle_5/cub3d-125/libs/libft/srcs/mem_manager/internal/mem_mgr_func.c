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

bool	mm_add_to_bucket(t_mem_manager *mgr, void *ptr)
{
	t_mem_header	*header;
	t_mem_block		*block;
	size_t			index;

	header = (t_mem_header *)ptr - 1;
	block = malloc(sizeof(t_mem_block));
	if (!block)
	{
		free(header);
		return (false);
	}
	index = mm_hash(header + 1);
	block->base = header;
	block->next = mgr->buckets[index];
	mgr->buckets[index] = block;
	return (true);
}

void	mm_free_one(t_mem_manager *mgr, void *ptr)
{
	t_mem_block		*prev;
	t_mem_block		*current;
	size_t			index;

	if (!ptr)
		return ;
	index = mm_hash(ptr);
	prev = NULL;
	current = mgr->buckets[index];
	while (current)
	{
		if (current->base + 1 == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				mgr->buckets[index] = current->next;
			return (free(current->base), free(current));
		}
		prev = current;
		current = current->next;
	}
}

void	mm_free_all(t_mem_manager *mgr)
{
	t_mem_block		*current;
	t_mem_block		*next;
	size_t			index;

	index = 0;
	while (index < MM_BUCKET_COUNT)
	{
		current = mgr->buckets[index];
		while (current)
		{
			next = current->next;
			free(current->base);
			free(current);
			current = next;
		}
		mgr->buckets[index++] = NULL;
	}
}
