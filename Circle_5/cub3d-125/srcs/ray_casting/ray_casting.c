/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:34:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/22 15:52:37 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	init_dda(t_vectors *v)
{
	if (v->ray_dir.x < 0)
	{
		v->step.x = -1;
		v->side.x = (v->pos.x - v->map.x) * v->delta.x;
	}
	else
	{
		v->step.x = 1;
		v->side.x = (v->map.x + 1.0 - v->pos.x) * v->delta.x;
	}
	if (v->ray_dir.y < 0)
	{
		v->step.y = -1;
		v->side.y = (v->pos.y - v->map.y) * v->delta.y;
	}
	else
	{
		v->step.y = 1;
		v->side.y = (v->map.y + 1.0 - v->pos.y) * v->delta.y;
	}
}

static inline bool	perform_dda(t_data *d, t_vectors *v)
{
	while (true)
	{
		if (v->side.x < v->side.y)
		{
			v->side.x += v->delta.x;
			v->map.x += v->step.x;
			if (d->map.map[v->map.y][v->map.x] == '1' ||
				(d->settings.door_close &&
					d->map.map[v->map.y][v->map.x] == 'D'))
				return (0);
		}
		else
		{
			v->side.y += v->delta.y;
			v->map.y += v->step.y;
			if (d->map.map[v->map.y][v->map.x] == '1' ||
				(d->settings.door_close &&
					d->map.map[v->map.y][v->map.x] == 'D'))
				return (1);
		}
	}
	return (0);
}

void	draw_view(t_data *d)
{
	double		camera_x;
	t_vectors	v;
	t_dda		dda;
	int			x;

	v.pos = get_player_pos(d);
	clear_render_buffer(d);
	x = 0;
	while (x < d->settings.render.width)
	{
		camera_x = 2.0 * x / d->settings.render.width - 1.0;
		v.map = (t_vectori){v.pos.x, v.pos.y};
		v.ray_dir = get_ray_dir(d->player.angle, camera_x);
		v.delta = get_delta_dist(v.ray_dir);
		init_dda(&v);
		dda.side_hit = perform_dda(d, &v);
		render_column(d, v, &dda, x);
		x++;
	}
	upscaling(d);
	push_frame(d);
}
