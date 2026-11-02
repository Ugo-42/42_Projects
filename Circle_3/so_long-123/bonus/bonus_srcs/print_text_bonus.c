/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugo <ugwentzi@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:38:39 by ugo               #+#    #+#             */
/*   Updated: 2025/03/05 09:05:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

uint32_t	rgb_to_abgr(uint32_t rgb)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	return ((0xFF << 24) | (b << 16) | (g << 8) | r);
}

static uint32_t	blend_color(uint32_t src, uint32_t target)
{
	uint8_t	alpha;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	alpha = (src >> 24) & 0xFF;
	b = (target >> 16) & 0xFF;
	g = (target >> 8) & 0xFF;
	r = target & 0xFF;
	return ((alpha << 24) | (b << 16) | (g << 8) | r);
}

static void	change_text_color(mlx_image_t *text_img, uint32_t color,
	bool smooth)
{
	size_t		x;
	size_t		y;
	size_t		i;
	uint32_t	*pixel;
	uint32_t	src_color;

	i = 0;
	while (i < text_img->width * text_img->height)
	{
		y = i / text_img->width;
		x = i % text_img->width;
		pixel = (uint32_t *)(text_img->pixels + (y * text_img->width + x)
				* sizeof(uint32_t));
		src_color = *pixel;
		if ((src_color & 0xFF000000) != 0)
		{
			*pixel = color;
			if (smooth)
				*pixel = blend_color(src_color, color);
		}
		i++;
	}
}

void	print_moves(t_data *data, char *text)
{
	size_t	size;
	size_t	x;
	size_t	y;

	x = data->tile_size / 2;
	y = data->tile_size / 2;
	size = 2;
	if (4 * data->map.width < data->map.height)
		size = 1;
	if (data->moves_text)
		mlx_delete_image(data->mlx, data->moves_text);
	if (!text)
		ft_cexit_error(1, "In 'print_text': " BAD_ARG, cleanup, data);
	data->moves_text = mlx_put_string(data->mlx, text, x, y);
	if (!data->moves_text)
		ft_cexit_error(1, "In 'print_text': " BAD_ALLOC, cleanup, data);
	if (!mlx_resize_image(data->moves_text,
			data->moves_text->width * size, data->moves_text->height * size))
	{
		ft_cexit_error(1, "In 'print_text': " BAD_ALLOC, cleanup, data);
	}
	change_text_color(data->moves_text, rgb_to_abgr(loop_color_value()), true);
	free(text);
}

void	print_days(t_data *data, char *text, uint32_t color_hex, bool smooth)
{
	size_t	x;
	size_t	y;

	x = data->map.width * data->tile_size - 200;
	if (data->story)
		x = data->map.width * data->tile_size - 820;
	y = data->tile_size / 2;
	if (data->days_text)
		mlx_delete_image(data->mlx, data->days_text);
	if (!text)
		ft_cexit_error(1, "In 'print_text': " BAD_ARG, cleanup, data);
	data->days_text = mlx_put_string(data->mlx, text, x, y);
	if (!data->days_text)
		ft_cexit_error(1, "In 'print_text': " BAD_ALLOC, cleanup, data);
	if (!mlx_resize_image(data->days_text,
			data->days_text->width * 2, data->days_text->height * 2))
	{
		ft_cexit_error(1, "In 'print_text': " BAD_ALLOC, cleanup, data);
	}
	change_text_color(data->days_text, rgb_to_abgr(color_hex), smooth);
	free(text);
}
