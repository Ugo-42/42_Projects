/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:45:15 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/22 15:15:03 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline mlx_image_t const	*choose_texture(
	t_data *d, t_vectors v, t_dda *dda)
{
	if (d->map.map[v.map.y][v.map.x] == 'D')
		return (d->image.d_image);
	if (dda->side_hit == true)
	{
		if (v.ray_dir.y < 0)
			return (d->image.no_image);
		else
			return (d->image.so_image);
	}
	else
	{
		if (v.ray_dir.x < 0)
			return (d->image.we_image);
		else
			return (d->image.ea_image);
	}
}

static inline int	calc_tex_x(mlx_image_t const *tex, t_vectors v, t_dda *dda)
{
	dda->tex_x = (int)(dda->wall_x * (double)tex->width);
	if ((dda->side_hit == false && v.ray_dir.x < 0)
		|| (dda->side_hit == true && !(v.ray_dir.y < 0)))
		dda->tex_x = tex->width - dda->tex_x - 1;
	return (dda->tex_x);
}

static void	draw_vertical_slice(t_data *d, mlx_image_t const *tex,
	t_dda *dda, int screen_x)
{
	t_draw		w;
	int			y;

	w.start = -dda->line_height / 2 + d->settings.render.height / 2;
	if (w.start < 0)
		w.start = 0;
	w.end = dda->line_height / 2 + d->settings.render.height / 2;
	if (w.end >= d->settings.render.height)
		w.end = d->settings.render.height - 1;
	w.wall_start = (d->settings.render.height - dda->line_height) / 2.0;
	w.dst = &d->buf.render[w.start * d->settings.render.width + screen_x];
	y = w.start - 1;
	while (++y <= w.end)
	{
		dda->tex_y = (y - w.wall_start)
			* ((double)tex->height / dda->line_height);
		if (dda->tex_y >= 0 && dda->tex_y < (int)tex->height)
		{
			w.px = &tex->pixels[4 * (dda->tex_y * tex->width + dda->tex_x)];
			w.color = ((uint32_t)w.px[3] << 24)
				| (w.px[2] << 16) | (w.px[1] << 8) | w.px[0];
			*w.dst = w.color;
		}
		w.dst += d->settings.render.width;
	}
}

static inline double	calc_perp_dist(t_vectors v, t_dda *dda)
{
	if (dda->side_hit == false)
		return ((v.map.x - v.pos.x + (1 - v.step.x) / 2.0) / v.ray_dir.x);
	else
		return ((v.map.y - v.pos.y + (1 - v.step.y) / 2.0) / v.ray_dir.y);
}

void	render_column(t_data *d, t_vectors v, t_dda *dda, int screen_x)
{
	mlx_image_t const	*tex = choose_texture(d, v, dda);

	dda->perp_dist = calc_perp_dist(v, dda);
	dda->line_height = d->settings.render.height / dda->perp_dist;
	if (dda->side_hit == false)
		dda->wall_x = v.pos.y + dda->perp_dist * v.ray_dir.y;
	else
		dda->wall_x = v.pos.x + dda->perp_dist * v.ray_dir.x;
	dda->wall_x -= floor(dda->wall_x);
	dda->tex_x = calc_tex_x(tex, v, dda);
	draw_vertical_slice(d, tex, dda, screen_x);
}
