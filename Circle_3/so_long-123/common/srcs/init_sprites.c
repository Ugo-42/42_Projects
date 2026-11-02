/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:22:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/04 14:23:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	place_sprite_instances(t_data *data, mlx_image_t *image,
	t_objs target)
{
	size_t	x;
	size_t	y;
	size_t	i;

	i = 0;
	while (i < data->map.width * data->map.height)
	{
		y = i / data->map.width;
		x = i % data->map.width;
		if (data->map.grid[y][x] == target || target == EMPTY)
		{
			mlx_image_to_window(data->mlx, image,
				x * data->tile_size, y * data->tile_size);
		}
		i++;
	}
}

static void	init_sprite(t_data *data, mlx_image_t **image,
	const char *texture_path, t_objs target)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_path);
	if (!texture)
	{
		ft_fcexit_error(1, ft_stringf("In 'init_sprite': "
				"Couldn't load '%s'.", texture_path), cleanup, data);
	}
	*image = mlx_texture_to_image(data->mlx, texture);
	if (!*image)
		ft_cexit_error(1, "In 'init_sprite': " BAD_ALLOC, cleanup, data);
	if (!mlx_resize_image(*image, data->tile_size, data->tile_size))
	{
		ft_cexit_error(1, "In 'init_sprite': Failed to resize image.",
			cleanup, data);
	}
	place_sprite_instances(data, *image, target);
	mlx_delete_texture(texture);
}

void	init_sprites(t_data *data)
{
	t_sprites	*sprites;

	sprites = &data->sprites;
	init_sprite(data, &sprites->empty, TTP_EMPTY, EMPTY);
	init_sprite(data, &sprites->walls, TTP_WALL, WALL);
	init_sprite(data, &sprites->exit, TTP_EXIT, EXIT);
	init_sprite(data, &sprites->collectibles, TTP_COLLECTIBLE, COLLECTIBLE);
	init_sprite(data, &sprites->player, TTP_PLAYER, PLAYER);
}
