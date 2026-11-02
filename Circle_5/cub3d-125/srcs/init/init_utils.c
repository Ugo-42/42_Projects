/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:45:50 by vvalenti          #+#    #+#             */
/*   Updated: 2025/08/26 12:13:45 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                  FPS                                       */
/* ************************************************************************** */

void	init_fps_images(t_data *d)
{
	char	*str;
	int		i;

	i = 0;
	while (i <= 60)
	{
		str = ft_stringf("FPS: %d", i);
		d->fps.fps_img[i] = mlx_put_string(d->mlx, str,
				d->settings.screen.width / 100,
				d->settings.screen.height / 100);
		if (d->fps.fps_img[i])
		{
			mlx_resize_image(d->fps.fps_img[i],
				d->fps.fps_img[i]->width * 2,
				d->fps.fps_img[i]->height * 2);
		}
		d->fps.fps_img[i++]->enabled = false;
		free(str);
	}
}

/* ************************************************************************** */
/*                                LOADING                                     */
/* ************************************************************************** */

mlx_image_t	*set_color(t_data *d, int sz_1, int sz_2, uint32_t color)
{
	int			x;
	int			y;
	mlx_image_t	*image;

	image = mlx_new_image(d->mlx, sz_1, sz_2);
	if (!image)
		ft_cexit_error(1, "mlx_new_image failed: cant set color", cleanup, d);
	y = -1;
	while (++y < sz_2)
	{
		x = -1;
		while (++x < sz_1)
		{
			mlx_put_pixel(image, x, y, color);
		}
	}
	return (image);
}

void	set_no_color(t_data *d, mlx_image_t **image, int sz_1, int sz_2)
{
	static uint32_t	color_1 = 0x000000FF;
	static uint32_t	color_2 = 0xFF00FFFF;
	int				x;
	int				y;

	*image = mlx_new_image(d->mlx, sz_1, sz_2);
	ft_fprintf(2, RED "Invalid color given, switching to no color\n%R");
	if (!*image)
		ft_cexit_error(1, "mlx_new_image failed: cant set color", cleanup, d);
	y = -1;
	while (++y < sz_2)
	{
		x = -1;
		while (++x < sz_1)
		{
			if ((x < sz_1 / 2 && y < sz_2 / 2)
				|| (x >= sz_1 / 2 && y >= sz_2 / 2))
				mlx_put_pixel(*image, x, y, color_1);
			else
				mlx_put_pixel(*image, x, y, color_2);
		}
	}
}

uint32_t	try_color(char *path)
{
	char		colors[3][4];
	int			i;
	int			j;
	int			k;

	j = -1;
	i = 0;
	ft_bzero(colors, sizeof(colors));
	while (++j < 3)
	{
		k = 0;
		while (ft_is_digit(path[i]) && k < 3)
		{
			colors[j][k++] = path[i++];
		}
		if ((j < 2 && path[i++] != ',')
			|| ft_atou(colors[j]) > 255)
			return (0);
	}
	if (!colors[0][0] || !colors[1][0] || !colors[2][0])
		return (0);
	if (path[i] != '\0')
		return (0);
	return (ft_atou(colors[0]) << 24 | ft_atou(colors[1]) << 16
		| ft_atou(colors[2]) << 8 | 0xFF);
}

void	assign_default_assets(t_data *d)
{
	d->assets.player = "textures/default/player.png";
	d->assets.no_path = "textures/default/no.png";
	d->assets.so_path = "textures/default/so.png";
	d->assets.ea_path = "textures/default/ea.png";
	d->assets.we_path = "textures/default/we.png";
	d->assets.c_path = "50,170,210";
	d->assets.f_path = "57,225,69";
}
