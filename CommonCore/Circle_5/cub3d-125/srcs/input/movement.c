/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:13:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 14:10:05 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static inline void	move_player(t_data *d)
{
	d->image.player->instances[0].x = d->player.x;
	d->image.player->instances[0].y = d->player.y;
}

static inline void	on_escape(t_data *d)
{
	if (d->menu.init_success)
	{
		mlx_set_cursor_mode(d->mlx, MLX_MOUSE_NORMAL);
		d->menu.enabled = true;
		d->menu.state = M_MAIN;
		d->menu.main->instances->enabled = true;
		handle_menu(d);
	}
	else
	{
		ft_cexit(0, cleanup, d);
	}
}

static inline bool	is_in_door(t_data *d, float x, float y)
{
	int const	ts = d->settings.tile_size;

	if (d->map.map[(int)y / ts][(int)x / ts] == 'D')
		return (true);
	return (false);
}

static bool	update_door(t_data *d)
{
	float const	w = d->image.player->width;
	float const	h = d->image.player->height;
	float const	x = d->player.x;
	float const	y = d->player.y;

	if (is_e_key_hit(d) && !is_in_door(d, x + w, y + h)
		&& !is_in_door(d, x + w, y) && !is_in_door(d, x, y + h)
		&& !is_in_door(d, x, y))
	{
		if (d->settings.door_close == false)
			d->settings.door_close = true;
		else
			d->settings.door_close = false;
		return (true);
	}
	return (false);
}

void	movement(void *data)
{
	t_data	*d;

	d = data;
	if (d->menu.enabled)
	{
		handle_menu(d);
		return ;
	}
	if (is_esc_hit(d))
		on_escape(d);
	update_movement(d);
	update_rotation(d);
	update_rotation_mouse(d);
	move_player(d);
	if (is_moving(d) || update_door(d))
	{
		draw_view(d);
		if (d->settings.map_visible)
			draw_map(d);
	}
}
