/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_updates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:59:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 15:21:52 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                            SLIDERS UPDATE                                  */
/* ************************************************************************** */

static void	update_slider_position(t_slider *s, int mouse_x, t_data *d)
{
	int const	bar_left = d->settings.screen.width * (s->bar.left / 100.0f);
	int const	bar_right = d->settings.screen.width * (s->bar.right / 100.0f);
	float		ball_center_x;

	if (mouse_x < bar_left)
		mouse_x = bar_left;
	if (mouse_x > bar_right)
		mouse_x = bar_right;
	s->ball->instances[0].x = mouse_x - s->ball->width / 2;
	s->value = (float)(mouse_x - bar_left) / (bar_right - bar_left);
	ball_center_x = s->ball->instances[0].x + s->ball->width / 2;
	s->bar_bg->instances[0].x = ball_center_x - s->bar_bg->width;
}

void	update_sliders(t_data *d)
{
	t_vectori	mouse;
	t_slider	*s;
	int			i;

	mlx_get_mouse_pos(d->mlx, &mouse.x, &mouse.y);
	i = 0;
	while (i < 3)
	{
		s = &d->menu.slider[i];
		if (s->held && is_left_held(d))
			update_slider_position(s, mouse.x, d);
		else
			s->held = false;
		i++;
	}
}

/* ************************************************************************** */
/*                           INSTANCES UPDATE                                 */
/* ************************************************************************** */

static inline void	disable_all_menu_instances(t_data *d)
{
	d->menu.main->instances->enabled = false;
	d->menu.settings->instances->enabled = false;
	d->menu.settings_bg->instances->enabled = false;
	d->menu.button[0].on->instances->enabled = false;
	d->menu.button[0].off->instances->enabled = false;
	d->menu.button[1].on->instances->enabled = false;
	d->menu.button[1].off->instances->enabled = false;
	d->menu.slider[0].ball->instances->enabled = false;
	d->menu.slider[0].bar_bg->instances->enabled = false;
	d->menu.slider[1].ball->instances->enabled = false;
	d->menu.slider[1].bar_bg->instances->enabled = false;
	d->menu.slider[2].ball->instances->enabled = false;
	d->menu.slider[2].bar_bg->instances->enabled = false;
}

static inline void	enable_settings_menu(t_data *d)
{
	d->menu.settings->instances->enabled = true;
	d->menu.settings_bg->instances->enabled = true;
	d->menu.slider[0].ball->instances->enabled = true;
	d->menu.slider[0].bar_bg->instances->enabled = true;
	d->menu.slider[1].ball->instances->enabled = true;
	d->menu.slider[1].bar_bg->instances->enabled = true;
	d->menu.slider[2].ball->instances->enabled = true;
	d->menu.slider[2].bar_bg->instances->enabled = true;
	if (d->settings.map_visible)
	{
		d->menu.button[0].on->instances->enabled = true;
		draw_map(d);
	}
	else
	{
		d->menu.button[0].off->instances->enabled = true;
		clear_image(d->image.mini_map);
	}
	if (d->settings.fps_visible)
		d->menu.button[1].on->instances->enabled = true;
	else
		d->menu.button[1].off->instances->enabled = true;
}

void	update_menu_instances(t_data *d)
{
	disable_all_menu_instances(d);
	if (d->menu.state == M_NONE)
		return ;
	else if (d->menu.state == M_MAIN)
		d->menu.main->instances->enabled = true;
	else if (d->menu.state == M_SETTINGS)
		enable_settings_menu(d);
}
