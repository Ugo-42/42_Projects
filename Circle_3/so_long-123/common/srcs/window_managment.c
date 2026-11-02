/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:29:47 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/27 16:29:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	resize_window(t_data *data)
{
	int32_t	screen_width;
	int32_t	screen_height;
	int32_t	tile_width;
	int32_t	tile_height;

	mlx_get_monitor_size(0, &screen_width, &screen_height);
	tile_width = (screen_width / data->map.width) * SIZE_PERCENTAGE / 100;
	tile_height = (screen_height / data->map.height) * SIZE_PERCENTAGE / 100;
	data->tile_size = tile_width;
	if (tile_width > tile_height)
		data->tile_size = tile_height;
	if (!data->tile_size)
		data->tile_size = 1;
	mlx_set_window_size(data->mlx, data->tile_size * data->map.width,
		data->tile_size * data->map.height);
}

void	center_window(t_data data)
{
	int32_t	screen_width;
	int32_t	screen_height;
	int32_t	window_x;
	int32_t	window_y;

	mlx_get_monitor_size(0, &screen_width, &screen_height);
	window_x = (screen_width - data.tile_size * data.map.width) / 2;
	window_y = (screen_height - data.tile_size * data.map.height) / 2;
	mlx_set_window_pos(data.mlx, window_x, window_y);
}
