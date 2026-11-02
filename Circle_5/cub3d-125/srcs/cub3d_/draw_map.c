/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:47:51 by vvalenti          #+#    #+#             */
/*   Updated: 2025/08/25 15:18:02 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                  MAP                                       */
/* ************************************************************************** */

static void	clear_image_rgba(mlx_image_t *img, uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t	color;
	uint32_t	*pixels;
	uint32_t	total;
	uint32_t	i;
	uint8_t		a;

	a = 50;
	if (!img)
		return ;
	color = r | (g << 8) | (b << 16) | (a << 24);
	pixels = (uint32_t *)img->pixels;
	total = img->width * img->height;
	i = 0;
	while (i < total)
	{
		pixels[i] = color;
		i++;
	}
}

static void	put_pixel_img(mlx_image_t *dst, int px, int py, uint8_t *src_px)
{
	uint32_t	*dst_px;
	uint32_t	color;

	if (src_px[3] == 0)
		return ;
	color = src_px[0]
		| (src_px[1] << 8)
		| (src_px[2] << 16)
		| (src_px[3] << 24);
	dst_px = (uint32_t *)dst->pixels;
	dst_px[py * dst->width + px] = color;
}

void	draw_texture(mlx_image_t *dst, mlx_image_t *src,
			int dst_x, int dst_y)
{
	uint32_t	x;
	uint32_t	y;
	int			px;
	int			py;
	uint8_t		*src_px;

	if (!dst || !src)
		return ;
	y = -1;
	while (++y < src->height)
	{
		x = -1;
		while (++x < src->width)
		{
			px = dst_x + x;
			py = dst_y + y;
			if (px >= 0 && py >= 0
				&& px < (int)dst->width && py < (int)dst->height)
			{
				src_px = &src->pixels[(y * src->width + x) * 4];
				put_pixel_img(dst, px, py, src_px);
			}
		}
	}
}

static void	fill_map(t_data *d, int x, int y)
{
	int	draw_x;
	int	draw_y;

	d->mmap.map_x = (int)((d->mmap.offset_x / MP_TILE_SZ)) + x;
	d->mmap.map_y = (int)((d->mmap.offset_y / MP_TILE_SZ)) + y;
	if (d->mmap.map_y >= 0 && d->mmap.map_y < d->map.height
		&& d->mmap.map_x >= 0 && d->mmap.map_x < d->map.len[d->mmap.map_y])
	{
		draw_x = (int)(x * MP_TILE_SZ - fmod(d->mmap.offset_x, MP_TILE_SZ));
		draw_y = (int)(y * MP_TILE_SZ - fmod(d->mmap.offset_y, MP_TILE_SZ));
		if (d->map.map[d->mmap.map_y][d->mmap.map_x] == '1')
		{
			draw_texture(d->image.mini_map, d->image.w_square, draw_x, draw_y);
		}
		else if (d->map.map[d->mmap.map_y][d->mmap.map_x] == 'D'
			&& d->settings.door_close)
			draw_texture(d->image.mini_map, d->image.d_square, draw_x, draw_y);
		else if (ft_is_in_set(d->map.map
				[d->mmap.map_y][d->mmap.map_x], "0NSEWD"))
		{
			draw_texture(d->image.mini_map, d->image.f_square, draw_x, draw_y);
		}
	}
}

void	draw_map(t_data *d)
{
	int	x;
	int	y;

	clear_image_rgba(d->image.mini_map, 100, 100, 100);
	y = -1;
	d->mmap.mn_x = (int)((d->player.x / d->settings.tile_size) * MP_TILE_SZ);
	d->mmap.mn_y = (int)((d->player.y / d->settings.tile_size) * MP_TILE_SZ);
	d->mmap.offset_x = d->mmap.mn_x - (MP_SIZE / 2);
	d->mmap.offset_y = d->mmap.mn_y - (MP_SIZE / 2);
	while (++y < (MP_SIZE / MP_TILE_SZ) + MP_TILE_SZ)
	{
		x = -1;
		while (++x < (MP_SIZE / MP_TILE_SZ) + MP_TILE_SZ)
		{
			fill_map(d, x, y);
		}
	}
	draw_texture(d->image.mini_map, d->image.mp_player,
		MP_SIZE / 2, MP_SIZE / 2);
}
