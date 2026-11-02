/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:29:47 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/11 13:21:26 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_window(t_data *d)
{
	int32_t	tile_width;
	int32_t	tile_height;

	if (!d->map.width || !d->map.height)
		return ;
	tile_width = (d->settings.screen.width / d->map.width)
		* SIZE_PERCENTAGE / 100;
	tile_height = (d->settings.screen.height / d->map.height)
		* SIZE_PERCENTAGE / 100;
	d->settings.tile_size = tile_width;
	if (tile_width > tile_height)
		d->settings.tile_size = tile_height;
	if (!d->settings.tile_size)
		d->settings.tile_size = 1;
	mlx_set_window_size(d->mlx, d->settings.screen.width,
		d->settings.screen.height);
}

void	center_window(t_data d)
{
	mlx_set_window_pos(d.mlx, 0, 0);
}
/*
void	resize_window(t_data *d)
{
	int32_t	tile_width;
	int32_t	tile_height;
	int32_t	new_width;
	int32_t	new_height;

	if (!d->map.width || !d->map.height)
		return ;
	tile_width = (d->settings.width / d->map.width) * SIZE_PERCENTAGE / 100;
	tile_height = (d->settings.height / d->map.height) * SIZE_PERCENTAGE / 100;
	d->settings.tile_size = tile_width;
	if (tile_width > tile_height)
		d->settings.tile_size = tile_height;
	if (!d->settings.tile_size)
		d->settings.tile_size = 1;
	new_width = d->settings.tile_size * d->map.width;
	new_height = d->settings.tile_size * d->map.height;
	if (new_width < 1 || new_height < 1)
		return ;
	mlx_set_window_size(d->mlx, d->settings.tile_size * d->map.width,
		d->settings.tile_size * d->map.height);
}

void	center_window(t_data d)
{
	int32_t	window_x;
	int32_t	window_y;

	window_x = (d.settings.width - d.settings.tile_size * d.map.width) / 2;
	window_y = (d.settings.height - d.settings.tile_size * d.map.height) / 2;
	if (window_x < 0 || window_y < 0)
		return ;
	mlx_set_window_pos(d.mlx, window_x, window_y);
}
*/
