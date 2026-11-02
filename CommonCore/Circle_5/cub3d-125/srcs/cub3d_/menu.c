/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:14:17 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 15:46:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                            INIT SETTINGS                                   */
/* ************************************************************************** */

static void	position_slider(t_data *d, t_slider *s)
{
	int const	bar_left = d->settings.screen.width * (s->bar.left / 100.0f);
	int const	bar_right = d->settings.screen.width * (s->bar.right / 100.0f);
	int const	pos_x = bar_left + s->value * (bar_right - bar_left);
	float		center_x;

	s->ball->instances->x = pos_x - s->ball->width / 2;
	center_x = s->ball->instances->x + s->ball->width / 2;
	s->bar_bg->instances->x = center_x - s->bar_bg->width;
}

void	handle_settings(t_data *d)
{
	static bool	init;
	int			i;

	d->menu.state = M_SETTINGS;
	update_menu_instances(d);
	if (init)
		return ;
	i = 0;
	while (i < 3)
	{
		position_slider(d, &d->menu.slider[i]);
		i++;
	}
	init = true;
}

/* ************************************************************************** */
/*                              MAIN MENU                                     */
/* ************************************************************************** */

static void	resume(t_data *d)
{
	t_vectori const	center = {
		d->settings.screen.width / 2,
		d->settings.screen.height / 2
	};

	d->menu.enabled = false;
	d->menu.state = M_NONE;
	update_menu_instances(d);
	mlx_set_cursor_mode(d->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(d->mlx, center.x, center.y);
}

static void	handle_button_main(t_data *d, t_vectori mouse)
{
	t_hitbox const	b[3] = {\
		{.left = 39.5f, .right = 60.9f, .top = 26.8f, .bot = 39.7f}, \
		{.left = 39.5f, .right = 60.9f, .top = 44.1f, .bot = 57.0f}, \
		{.left = 39.5f, .right = 60.9f, .top = 61.4f, .bot = 74.1f},
	};
	t_vector const	percent = {
		.x = (double)mouse.x / d->settings.screen.width * 100.0,
		.y = (double)mouse.y / d->settings.screen.height * 100.0
	};

	if (is_inside(b[0], percent))
		return (resume(d));
	else if (is_inside(b[1], percent))
		return (handle_settings(d));
	else if (is_inside(b[2], percent))
		return (ft_cexit(0, cleanup, d));
}

void	handle_menu(t_data *d)
{
	t_vectori	mouse;

	if (is_esc_hit(d))
	{
		if (d->settings.tex_size != d->settings.curr_tex_size)
			reload_textures(d);
		if (d->menu.state == M_MAIN)
			return (resume(d));
		else if (d->menu.state == M_SETTINGS)
		{
			d->menu.state = M_MAIN;
			update_menu_instances(d);
		}
	}
	if (is_left_clicked(d))
	{
		mlx_get_mouse_pos(d->mlx, &mouse.x, &mouse.y);
		if (d->menu.state == M_MAIN)
			handle_button_main(d, mouse);
		else if (d->menu.state == M_SETTINGS)
			handle_button_settings(d, mouse);
	}
	update_sliders(d);
	apply_slider_settings(d);
	draw_view(d);
}
