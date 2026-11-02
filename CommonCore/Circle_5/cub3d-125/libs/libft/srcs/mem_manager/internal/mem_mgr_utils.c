/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:53:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/15 10:12:08 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal/mem_manager.h"
#include "libft.h"

#define GOLDEN_RATIO 0x9E3779B97F4A7C15ULL

#define MULT1 0xBF58476D1CE4E5B9ULL
#define MULT2 0x94D049BB133111EBULL
#define MULT3 0xA3C9A207F6A1BC33ULL

size_t	mm_hash(void *ptr)
{
	size_t	x;

	x = (size_t)ptr ^ GOLDEN_RATIO;
	x = (x ^ (x >> 27)) * MULT1;
	x = (x ^ (x >> 32)) * MULT2;
	x = (x ^ (x >> 24)) * MULT3;
	return (x & (MM_BUCKET_COUNT - 1));
}

#ifndef DEBUG

bool	internal_manager(t_mem_func func, void *ptr)
{
	static t_mem_manager	mem_mgr;

	if (func == MM_ADD)
		return (mm_add_to_bucket(&mem_mgr, ptr));
	else if (func == MM_FREE)
		mm_free_one(&mem_mgr, ptr);
	else if (func == MM_DESTROY)
		mm_free_all(&mem_mgr);
	else
		return (false);
	return (true);
}

#else

bool	internal_manager(t_mem_func func, void *ptr)
{
	static t_mem_manager	mem_mgr;

	if (func == MM_ADD)
		return (mm_add_to_bucket(&mem_mgr, ptr));
	else if (func == MM_FREE)
		mm_free_one(&mem_mgr, ptr);
	else if (func == MM_DESTROY)
		mm_free_all(&mem_mgr);
	else if (func == MM_DEBUG)
		mm_analyze_collisions(&mem_mgr);
	else
		return (false);
	return (true);
}

# define TITLE "\033[1;38;2;117;85;170m"
# define TBL   "\033[38;2;136;32;160m"
# define TXT   "\033[38;2;80;191;191m"
# define BTXT  "\033[1;38;2;80;191;191m"

void	_print_collisions_result(t_debug_collisions c)
{
	ft_printf(
		TBL "╭──────────────────────────────────────╮\n"
		TBL "│" TITLE "    Memory Manager Collision Info     %R" TBL "│\n"
		TBL "├──────────────────────────────────────┤\n"
		TBL "│" TXT " Total Buckets:             " BTXT "%>u   %R" TBL "│\n"
		TBL "│" TXT " Total Pointers:            " BTXT "%>u   %R" TBL "│\n"
		TBL "│" TXT " Buckets with Collisions:   " BTXT "%>u   %R" TBL "│\n"
		TBL "│" TXT " Empty Buckets:             " BTXT "%>u   %R" TBL "│\n"
		TBL "│" TXT " Max Bucket Depth:          " BTXT "%>u   %R" TBL "│\n"
		TBL "│" TXT " Collision Percentage:      " BTXT "%>u   %R" TBL "│\n"
		TBL "╰──────────────────────────────────────╯%R\n",
		7, MM_BUCKET_COUNT,
		7, c.total_pointers,
		7, c.total_collisions,
		7, c.empty_buckets,
		7, c.max_depth,
		7, (c.total_collisions * 100) / MM_BUCKET_COUNT);
}

void	mm_analyze_collisions(t_mem_manager *mgr)
{
	t_mem_block			*current;
	t_debug_collisions	c;

	ft_bzero(&c, sizeof(c));
	while (c.index < MM_BUCKET_COUNT)
	{
		current = mgr->buckets[c.index];
		if (!current)
			c.empty_buckets++;
		else if (current->next)
			c.total_collisions++;
		c.depth = 0;
		while (current)
		{
			c.total_pointers++;
			c.depth++;
			current = current->next;
		}
		if (c.depth > c.max_depth)
			c.max_depth = c.depth;
		c.index++;
	}
	_print_collisions_result(c);
}

#endif
