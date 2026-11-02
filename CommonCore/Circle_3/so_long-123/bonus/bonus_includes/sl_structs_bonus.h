/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_structs_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 13:11:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_STRUCTS_BONUS_H
# define SL_STRUCTS_BONUS_H

# include "MLX42.h"

typedef enum e_objs
{
	EMPTY		= '0',
	WALL		= '1',
	BLACK_HOLE	= 'B',
	COLLECTIBLE = 'C',
	EXIT		= 'E',
	FAILED		= 'F',
	PLAYER		= 'P',
}	t_objs;

typedef struct s_objs_count
{
	size_t	empty;
	size_t	walls;
	size_t	collectibles;
	size_t	failed;
	size_t	exit;
	size_t	player;
	size_t	black_hole;
}	t_objs_count;

typedef struct s_sprites
{
	mlx_image_t	*empty;
	mlx_image_t	*player;
	mlx_image_t	*walls;
	mlx_image_t	*collectibles;
	mlx_image_t	*failed;
	mlx_image_t	*exit;
}	t_sprites;

typedef struct s_black_hole
{
	mlx_image_t	*immobile;
	mlx_image_t	*bh[2][8];
	size_t		speed;
	double		bh_update;
	double		days_update;
}	t_black_hole;

typedef struct s_map
{
	t_objs			**grid;
	size_t			alloc_size;
	size_t			width;
	size_t			height;
	t_objs_count	count;
	size_t			wall_count;
}	t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*moves_text;
	mlx_image_t		*days_text;
	size_t			moves;
	int				days;
	bool			endless;
	bool			story;
	t_map			map;
	t_sprites		sprites;
	t_black_hole	black_hole;
	int				ber_file_fd;
	size_t			tile_size;
}	t_data;

#endif
