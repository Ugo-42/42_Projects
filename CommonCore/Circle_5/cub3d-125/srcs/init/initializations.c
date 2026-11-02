/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:14:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 14:36:30 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_direction(t_player *p)
{
	if (p->view == 'N')
	{
		p->angle = 3 * M_PI / 2;
	}
	else if (p->view == 'S')
	{
		p->angle = M_PI / 2;
	}
	else if (p->view == 'E')
	{
		p->angle = 0;
	}
	else if (p->view == 'W')
	{
		p->angle = M_PI;
	}
}

static void	set_windows(t_data *d)
{
	mlx_get_monitor_size(0,
		&d->settings.screen.width, &d->settings.screen.height);
	resize_window(d);
	center_window(*d);
	mlx_set_mouse_pos(d->mlx, d->settings.screen.width / 2,
		d->settings.screen.height / 2);
}

static void	set_default(t_data *d)
{
	d->player.x = (d->player.x * d->settings.tile_size)
		+ (d->settings.tile_size / 4);
	d->player.y = (d->player.y * d->settings.tile_size)
		+ (d->settings.tile_size / 4);
	d->settings.display.width = d->settings.screen.width;
	d->settings.display.height = d->settings.screen.height;
	d->settings.render.width = DEFAULT_RENDER_WIDTH;
	d->settings.render.height = DEFAULT_RENDER_HEIGHT;
	d->settings.scale.x = d->settings.display.width / d->settings.render.width;
	d->settings.scale.y = d->settings.display.height
		/ d->settings.render.height;
	d->settings.fov = FOV;
	d->settings.map_bg = DEFAULT_MAP_BG_COLOR;
	d->settings.map_fg = DEFAULT_MAP_FG_COLOR;
	d->settings.map_dg = DEFAULT_MAP_DG_COLOR;
	d->settings.movement_speed = d->settings.tile_size / 200.0f;
	d->settings.rotation_speed = (M_PI / 180.0f) / 8.0f;
	d->settings.map_visible = true;
	d->settings.fps_visible = true;
	d->settings.door_close = true;
	d->settings.view_color = DEFAULT_VIEW_COLOR;
	gettimeofday(&d->fps.last_time, NULL);
	set_player_direction(&d->player);
}

static void	init_buffers(t_data *d)
{
	d->buf.frame = mm_alloc(
			MAX_RESOLUTION_WIDTH * MAX_RESOLUTION_HEIGHT * sizeof(uint32_t));
	d->buf.render = mm_alloc(
			MAX_RESOLUTION_WIDTH * MAX_RESOLUTION_HEIGHT * sizeof(uint32_t));
	d->image.view = mlx_new_image(d->mlx,
			d->settings.screen.width, d->settings.screen.height);
	d->image.view_map = mlx_new_image(d->mlx,
			d->settings.screen.width, d->settings.screen.height);
	if (!d->image.view_map || !d->image.view)
		ft_cexit_error(0, "Mlx load fail", cleanup, d);
	if (mlx_image_to_window(d->mlx, d->image.view_map, 0, 0) < 0
		|| (mlx_image_to_window(d->mlx, d->image.player, 0, 0) < 0)
		|| (mlx_image_to_window(d->mlx, d->image.view, 0, 0) < 0)
		|| (mlx_image_to_window(d->mlx, d->image.mini_map,
				d->settings.screen.width - MP_SIZE, 0)))
		ft_cexit_error(1, "Failed to draw image to window", cleanup, d);
}

bool	init_data(t_data *d)
{
	d->mlx = mlx_init(1, 1, "oui's cub3d", false);
	if (!d->mlx)
		return (false);
	set_windows(d);
	set_default(d);
	load_textures(d);
	init_buffers(d);
	init_fps_images(d);
	init_menu(d);
	return (true);
}
