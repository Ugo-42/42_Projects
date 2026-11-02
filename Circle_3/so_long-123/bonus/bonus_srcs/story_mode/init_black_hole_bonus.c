/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_black_hole.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:37:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 09:04:57 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	place_bh_instances(t_data *data, mlx_image_t *image)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	while (i < data->map.width * data->map.height)
	{
		y = i / data->map.width;
		x = i % data->map.width;
		if (data->map.grid[y][x] == BLACK_HOLE)
		{
			mlx_image_to_window(data->mlx, image,
				x * data->tile_size, y * data->tile_size);
			image->instances->enabled = false;
		}
		i++;
	}
}

static void	init_bh_sprites(t_data *data, mlx_image_t **image,
	const char *texture_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_path);
	if (!texture)
	{
		ft_fcexit_error(1, ft_stringf("In 'init_bh_sprites': "
				"Couldn't load '%s'.", texture_path), cleanup, data);
	}
	*image = mlx_texture_to_image(data->mlx, texture);
	if (!*image)
	{
		ft_cexit_error(1, "In 'init_bh_sprites': " BAD_ALLOC, cleanup, data);
	}
	if (!mlx_resize_image(*image, data->tile_size, data->tile_size))
	{
		ft_cexit_error(1, "In 'init_bh_sprites': "
			"Failed to resize image.", cleanup, data);
	}
	place_bh_instances(data, *image);
	mlx_delete_texture(texture);
}

static void	init_immobile_black_hole(t_data *data)
{
	char	*texture_path;

	texture_path = ft_stringf("sprites/story/black_hole/black_hole.png");
	if (!texture_path)
	{
		ft_cexit_error(1, "In 'init_immobile_black_hole': " BAD_ALLOC,
			cleanup, data);
	}
	init_bh_sprites(data, &data->black_hole.immobile, texture_path);
	data->black_hole.immobile->instances->enabled = true;
	free(texture_path);
}

void	init_black_hole(t_data *data)
{
	char	*texture_path;
	size_t	layer;
	size_t	angle;
	size_t	i;

	i = 0;
	while (i < 2 * 8)
	{
		layer = i / 8;
		angle = i % 8;
		texture_path = ft_stringf("sprites/story/black_hole/bh_%d-%d.png",
				layer, angle * 45);
		if (!texture_path)
		{
			ft_cexit_error(1, "In 'init_black_hole': " BAD_ALLOC,
				cleanup, data);
		}
		init_bh_sprites(data, &data->black_hole.bh[layer][angle], texture_path);
		free(texture_path);
		i++;
	}
	init_immobile_black_hole(data);
}
