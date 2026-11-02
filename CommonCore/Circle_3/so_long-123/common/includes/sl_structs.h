/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 13:57:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_STRUCTS_H
# define SL_STRUCTS_H

# include "MLX42.h"

typedef enum e_objs
{
	EMPTY		= '0',
	WALL		= '1',
	COLLECTIBLE = 'C',
	EXIT		= 'E',
	PLAYER		= 'P',
}	t_objs;

typedef struct s_objs_count
{
	size_t	empty;
	size_t	walls;
	size_t	collectibles;
	size_t	exit;
	size_t	player;
}	t_objs_count;

typedef struct s_sprites
{
	mlx_image_t	*empty;
	mlx_image_t	*player;
	mlx_image_t	*walls;
	mlx_image_t	*collectibles;
	mlx_image_t	*exit;
}	t_sprites;

typedef struct s_map
{
	t_objs			**grid;
	size_t			alloc_size;
	size_t			width;
	size_t			height;
	t_objs_count	count;
}	t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	t_map			map;
	t_sprites		sprites;
	size_t			tile_size;
	size_t			moves;
	int				ber_file_fd;
}	t_data;

#endif
