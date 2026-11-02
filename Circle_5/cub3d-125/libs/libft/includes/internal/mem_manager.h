/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/04 10:08:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_MANAGER_H
# define MEM_MANAGER_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

/* MUST be power of two !! */
# define MM_BUCKET_COUNT 1024

/* Internal Structs */

typedef struct s_mem_block		t_mem_block;
typedef struct s_mem_header		t_mem_header;
typedef struct s_mem_manager	t_mem_manager;

/* --- */

struct s_mem_header
{
	size_t	size;
};

struct s_mem_block
{
	t_mem_header	*base;
	t_mem_block		*next;
};

struct s_mem_manager
{
	t_mem_block	*buckets[MM_BUCKET_COUNT];
};

typedef enum e_mem_func			t_mem_func;

/* Internal Functions */
size_t	mm_hash(void *ptr);
bool	internal_manager(t_mem_func func, void *ptr);
bool	mm_add_to_bucket(t_mem_manager *mgr, void *ptr);
void	mm_free_all(t_mem_manager *mgr);
void	mm_free_one(t_mem_manager *mgr, void *ptr);

# ifndef DEBUG

enum e_mem_func
{
	MM_ADD,
	MM_DESTROY,
	MM_FREE
};

# else

typedef enum e_mem_func
{
	MM_ADD,
	MM_DEBUG,
	MM_DESTROY,
	MM_FREE
}	t_mem_func;

typedef struct s_debug_collisions
{
	unsigned int	depth;
	unsigned int	empty_buckets;
	unsigned int	index;
	unsigned int	max_depth;
	unsigned int	total_collisions;
	unsigned int	total_pointers;
}	t_debug_collisions;

void	mm_analyze_collisions(t_mem_manager *mgr);

# endif

#endif
