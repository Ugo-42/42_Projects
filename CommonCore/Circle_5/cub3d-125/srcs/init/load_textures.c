/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:16:33 by vvalenti          #+#    #+#             */
/*   Updated: 2025/08/26 12:14:22 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                LOADING                                     */
/* ************************************************************************** */

void	load_image(t_data *d, char *path, mlx_image_t **image, int size)
{
	int				fd;
	mlx_texture_t	*texture;
	uint32_t		color;

	fd = open(path, O_RDONLY, NULL);
	if (fd == -1)
	{
		ft_fprintf(2, BOLD "load_image():%R Couldn't open '%s'\n"
			"Switching to color\n", path);
		color = try_color(path);
		if (!color)
			return (set_no_color(d, image, size, size));
		*image = set_color(d, size, size, color);
		return ;
	}
	close(fd);
	texture = mlx_load_png(path);
	if (!texture)
		ft_cexit_error(1, "Mlx load fail", cleanup, d);
	*image = mlx_texture_to_image(d->mlx, texture);
	if (!*image)
		ft_cexit_error(1, "Mlx load fail", cleanup, d);
	mlx_delete_texture(texture);
	if (size > 0 && !mlx_resize_image(*image, size, size))
		ft_cexit_error(1, "Mlx resize fail", cleanup, d);
}

static void	load_color(t_data *d, char *path, mlx_image_t **image)
{
	uint32_t	color;
	int			fd;

	fd = open(path, O_RDONLY, NULL);
	if (fd != -1)
	{
		ft_fprintf(2, BOLD "load_color():%R File detected: %s\n"
			"Switching to png\n", path);
		close(fd);
		load_image(d, path, image, d->settings.screen.width);
		if (!mlx_resize_image(*image, d->settings.screen.width,
				d->settings.screen.height / 2))
			ft_cexit_error(1, "Mlx resize fail", cleanup, d);
		if (!mlx_resize_image(*image, d->settings.screen.width,
				d->settings.screen.height / 2))
			ft_cexit_error(1, "Mlx resize fail", cleanup, d);
		return ;
	}
	color = try_color(path);
	if (!color)
		set_no_color(d, image, d->settings.screen.width,
			d->settings.screen.height / 2);
	else
		*image = set_color(d, d->settings.screen.width,
				d->settings.screen.height / 2, color);
}

static void	load_square(t_data *d, mlx_image_t **image, uint32_t color)
{
	int	i;
	int	j;

	i = -1;
	(void)d;
	while (++i < MP_TILE_SZ)
	{
		j = -1;
		while (++j < MP_TILE_SZ)
			mlx_put_pixel(*image, i, j, color);
	}
}

/* ************************************************************************** */
/*                              INIT TEXTURES                                 */
/* ************************************************************************** */

static void	set_mini_map(t_data *d)
{
	d->image.w_square = mlx_new_image(d->mlx, MP_TILE_SZ, MP_TILE_SZ);
	d->image.f_square = mlx_new_image(d->mlx, MP_TILE_SZ, MP_TILE_SZ);
	d->image.d_square = mlx_new_image(d->mlx, MP_TILE_SZ, MP_TILE_SZ);
	d->image.mini_map = mlx_new_image(d->mlx, MP_SIZE, MP_SIZE);
	if (!d->image.w_square || !d->image.f_square || !d->image.mini_map)
		ft_cexit_error(0, "Mlx new image fail", cleanup, d);
	load_square(d, &d->image.w_square, d->settings.map_bg);
	load_square(d, &d->image.f_square, d->settings.map_fg);
	load_square(d, &d->image.d_square, d->settings.map_dg);
	draw_map(d);
}

void	load_textures(t_data *d)
{
	mlx_texture_t	*icon;

	load_image(d, d->assets.no_path, &d->image.no_image, DEFAULT_TEXTURE_SIZE);
	load_image(d, d->assets.so_path, &d->image.so_image, DEFAULT_TEXTURE_SIZE);
	load_image(d, d->assets.ea_path, &d->image.ea_image, DEFAULT_TEXTURE_SIZE);
	load_image(d, d->assets.we_path, &d->image.we_image, DEFAULT_TEXTURE_SIZE);
	load_image(d, "textures/default/door.png", &d->image.d_image,
		DEFAULT_TEXTURE_SIZE);
	load_color(d, d->assets.f_path, &d->image.f_image);
	load_color(d, d->assets.c_path, &d->image.c_image);
	load_image(d, d->assets.player, &d->image.player,
		d->settings.tile_size / 2);
	d->image.player->enabled = false;
	load_image(d, d->assets.player, &d->image.mp_player,
		MP_TILE_SZ / 2);
	mlx_image_to_window(d->mlx, d->image.c_image, 0, 0);
	mlx_image_to_window(d->mlx, d->image.f_image, 0,
		d->settings.screen.height / 2);
	icon = mlx_load_png("textures/icon/icon.png");
	if (!icon)
		ft_fprintf(2, "Couldn't load the icon\n");
	else
		mlx_set_icon(d->mlx, icon);
	mlx_delete_texture(icon);
	set_mini_map(d);
}
