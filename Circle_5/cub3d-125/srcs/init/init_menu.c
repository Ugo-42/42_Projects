/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:14:46 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 14:16:46 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                               PNG LOADER                                   */
/* ************************************************************************** */

bool	load_png_to_window(t_data *d, t_img_config c)
{
	mlx_texture_t	*texture;
	t_vectori		size;
	t_vectori		offset;

	size.y = d->settings.screen.height / c.scale_divisor;
	size.x = c.origin_size.x * size.y / c.origin_size.y;
	offset.x = d->settings.screen.width * c.percent.x - size.x / 2;
	offset.y = d->settings.screen.height * c.percent.y - size.y / 2;
	if (!is_valid_path(c.path))
		return (false);
	texture = mlx_load_png(c.path);
	if (!texture)
		return (false);
	*c.img = mlx_texture_to_image(d->mlx, texture);
	mlx_delete_texture(texture);
	if (!*c.img)
		return (false);
	if (!mlx_resize_image(*c.img, size.x, size.y))
		return (false);
	if (mlx_image_to_window(d->mlx, *c.img, offset.x, offset.y) == -1)
		return (false);
	(*c.img)->instances->enabled = false;
	return (true);
}

/* ************************************************************************** */
/*                             ASSETS LOADER                                  */
/* ************************************************************************** */

#define BTN_ON  "textures/menu/menu-settings_on.png"
#define BTN_OFF "textures/menu/menu-settings_off.png"
#define ST_BG   "textures/menu/menu-settings_bg.png"
#define MENU    "textures/menu/menu.png"
#define ST_MENU "textures/menu/menu-settings.png"
#define SL_BG   "textures/menu/menu-settings_slider_bg.png"
#define SL_BALL "textures/menu/menu-settings_ball.png"

bool	load_settings_button(t_data *d)
{
	t_img_config const	buttons[] = {\
		{&d->menu.settings_bg, ST_BG, {1080, 1080}, {0.64f, 0.546f}, 2.0f}, \
		{&d->menu.button[1].on, BTN_ON, {1920, 432}, {0.64f, 0.548f}, 10}, \
		{&d->menu.button[1].off, BTN_OFF, {1920, 432}, {0.64f, 0.548f}, 10}, \
		{&d->menu.button[0].on, BTN_ON, {1920, 432}, {0.64f, 0.460f}, 10}, \
		{&d->menu.button[0].off, BTN_OFF, {1920, 432}, {0.64f, 0.460f}, 10}, \
		{&d->menu.slider[0].bar_bg, SL_BG, {4480, 251}, {0.5f, 0.374f}, 42}, \
		{&d->menu.slider[1].bar_bg, SL_BG, {4480, 251}, {0.5f, 0.63f}, 42}, \
		{&d->menu.slider[2].bar_bg, SL_BG, {4480, 251}, {0.5f, 0.716f}, 42}, \
		{&d->menu.main, MENU, {2560, 1440}, {0.5f, 0.5f}, 1.5f}, \
		{&d->menu.settings, ST_MENU, {2560, 1440}, {0.5f, 0.5f}, 1.5f}, \
		{&d->menu.slider[0].ball, SL_BALL, {251, 251}, {0.5f, 0.374f}, 42}, \
		{&d->menu.slider[1].ball, SL_BALL, {251, 251}, {0.5f, 0.63f}, 42}, \
		{&d->menu.slider[2].ball, SL_BALL, {251, 251}, {0.5f, 0.716f}, 42}, \
	};
	int const			nb_assets = sizeof(buttons) / sizeof(buttons[0]);
	int					i;

	i = 0;
	while (i < nb_assets)
	{
		if (!load_png_to_window(d, buttons[i++]))
			return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                           MENU INITIALIZATION                              */
/* ************************************************************************** */

void	init_renders(t_data *d)
{
	int const	divisor[] = {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60};
	int const	count = sizeof(divisor) / sizeof(divisor[0]);
	int			i;

	i = 0;
	while (i < count)
	{
		d->settings.renders[i].width = 1920 / divisor[i];
		d->settings.renders[i].height = 1080 / divisor[i];
		i++;
	}
	d->settings.nb_renders = count;
}

void	init_tex_sizes(t_data *d)
{
	int const	sizes[] = {8, 16, 32, 64, 128, 256, 512, 1024};
	int			i;

	d->settings.nb_tex_sizes = sizeof(sizes) / sizeof(sizes[0]);
	i = 0;
	while (i < d->settings.nb_tex_sizes)
	{
		d->settings.tex_sizes[i] = sizes[i];
		i++;
	}
	d->settings.tex_size = DEFAULT_TEXTURE_SIZE;
	d->settings.curr_tex_size = d->settings.tex_size;
}

void	init_menu(t_data *d)
{
	init_renders(d);
	init_tex_sizes(d);
	d->menu.enabled = false;
	d->menu.slider[0].bar = (t_hitbox){53.0f, 75.0f, 36.3f, 38.3f};
	d->menu.slider[1].bar = (t_hitbox){53.0f, 75.0f, 62.0f, 64.0f};
	d->menu.slider[2].bar = (t_hitbox){53.0f, 75.0f, 70.7f, 72.7f};
	d->menu.button[0].hitbox = (t_hitbox){53.4f, 74.8f, 43.1f, 48.8f};
	d->menu.button[1].hitbox = (t_hitbox){53.4f, 74.8f, 52.2f, 57.7f};
	d->menu.slider[0].value = 0.5f;
	d->menu.slider[1].value = 1.0f;
	d->menu.slider[2].value = 1.0f;
	d->menu.slider[0].held = false;
	d->menu.slider[1].held = false;
	d->menu.slider[2].held = false;
	mlx_set_cursor_mode(d->mlx, MLX_MOUSE_HIDDEN);
	if (!load_settings_button(d))
	{
		d->menu.init_success = false;
		return ;
	}
	d->menu.init_success = true;
}
