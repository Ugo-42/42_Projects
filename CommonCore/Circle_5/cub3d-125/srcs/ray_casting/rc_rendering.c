/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:34:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/18 11:03:49 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                               RENDERING                                    */
/* ************************************************************************** */

void	clear_render_buffer(t_data *d)
{
	ft_bzero(d->buf.render, sizeof(uint32_t)
		* d->settings.render.height * d->settings.render.width);
}

void	push_frame(t_data *d)
{
	uint32_t	*buf;

	if (d->settings.scale.x == 1 && d->settings.scale.y == 1)
		buf = d->buf.render;
	else
		buf = d->buf.frame;
	ft_memcpy(d->image.view->pixels, buf, sizeof(uint32_t)
		* d->settings.display.width * d->settings.display.height);
}

/* ************************************************************************** */
/*                               UPSCALING                                    */
/* ************************************************************************** */

static void	upscale_pixel(t_data *d, int x, int y)
{
	uint32_t const	color = d->buf.render[y * d->settings.render.width + x];
	int				dx;
	int				dy;

	dy = 0;
	while (dy < d->settings.scale.y)
	{
		dx = 0;
		while (dx < d->settings.scale.x)
		{
			d->buf.frame[(y * d->settings.scale.y + dy)
				* d->settings.display.width + (x * d->settings.scale.x + dx)]
				= color;
			dx++;
		}
		dy++;
	}
}

void	upscaling(t_data *d)
{
	int	x;
	int	y;

	if (d->settings.scale.x == 1 && d->settings.scale.y == 1)
		return ;
	y = 0;
	while (y < d->settings.render.height)
	{
		x = 0;
		while (x < d->settings.render.width)
		{
			upscale_pixel(d, x, y);
			x++;
		}
		y++;
	}
}
