/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:45:22 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/26 15:59:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_win(t_data *data)
{
	mlx_instance_t	*player;
	mlx_instance_t	*exit;

	player = data->sprites.player->instances;
	exit = data->sprites.exit->instances;
	if (data->map.count.collectibles == 0 && player->x == exit->x
		&& player->y == exit->y)
	{
		mlx_close_window(data->mlx);
	}
}

static void	check_collectible(t_data *data)
{
	mlx_instance_t	*player;
	mlx_instance_t	*collectible;
	size_t			i;

	player = data->sprites.player->instances;
	collectible = data->sprites.collectibles->instances;
	i = 0;
	while (i < data->sprites.collectibles->count)
	{
		if (player->x == collectible[i].x && player->y == collectible[i].y
			&& collectible[i].enabled)
		{
			collectible[i].enabled = false;
			data->map.count.collectibles--;
		}
		i++;
	}
}

static bool	collision(t_data *data, int nx, int ny)
{
	mlx_instance_t	*player;
	mlx_instance_t	*wall;
	size_t			i;

	player = data->sprites.player->instances;
	wall = data->sprites.walls->instances;
	i = 0;
	while (i < data->sprites.walls->count)
	{
		if (player->x == wall[i].x + nx && player->y == wall[i].y + ny)
			return (true);
		i++;
	}
	return (false);
}

static bool	move_player(t_data *data, int key_pressed, int *x, int *y)
{
	size_t	tile_size;

	tile_size = data->tile_size;
	if (key_pressed == MLX_KEY_UP && !collision(data, 0, tile_size))
		return (*y -= tile_size);
	else if (key_pressed == MLX_KEY_DOWN && !collision(data, 0, -tile_size))
		return (*y += tile_size);
	else if (key_pressed == MLX_KEY_LEFT && !collision(data, tile_size, 0))
		return (*x -= tile_size);
	else if (key_pressed == MLX_KEY_RIGHT && !collision(data, -tile_size, 0))
		return (*x += tile_size);
	return (0);
}

void	keyinput(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(data->mlx);
	}
	else if (keydata.action != MLX_RELEASE)
	{
		if (move_player(data, keydata.key,
				&data->sprites.player->instances->x,
				&data->sprites.player->instances->y))
		{
			loop_color();
			ft_printf("%d\n", ++data->moves);
			reset_color();
		}
		check_collectible(data);
		check_win(data);
	}
}
