/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:14:17 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 16:59:11 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                           TEXTURE RELOADER                                 */
/* ************************************************************************** */

void	reload_textures(t_data *d)
{
	mlx_delete_image(d->mlx, d->image.no_image);
	mlx_delete_image(d->mlx, d->image.so_image);
	mlx_delete_image(d->mlx, d->image.ea_image);
	mlx_delete_image(d->mlx, d->image.we_image);
	mlx_delete_image(d->mlx, d->image.d_image);
	load_image(d, d->assets.no_path, &d->image.no_image, d->settings.tex_size);
	load_image(d, d->assets.so_path, &d->image.so_image, d->settings.tex_size);
	load_image(d, d->assets.ea_path, &d->image.ea_image, d->settings.tex_size);
	load_image(d, d->assets.we_path, &d->image.we_image, d->settings.tex_size);
	load_image(d, "textures/default/door.png", &d->image.d_image,
		d->settings.tex_size);
	d->settings.curr_tex_size = d->settings.tex_size;
}

/* ************************************************************************** */
/*                           HANDLE SETTINGS                                  */
/* ************************************************************************** */

void	apply_slider_settings(t_data *d)
{
	float const	min_sens = (M_PI / 180.0f) / 32.0f;
	float const	max_sens = (M_PI / 180.0f) / 2.0f;
	int			step_tex;
	int			step;

	d->settings.rotation_speed = min_sens
		+ d->menu.slider[0].value * (max_sens - min_sens);
	step_tex = (int)(d->menu.slider[1].value
			* (d->settings.nb_tex_sizes - 1) + 0.5f);
	if (step_tex < 0)
		step_tex = 0;
	if (step_tex >= d->settings.nb_tex_sizes)
		step_tex = d->settings.nb_tex_sizes - 1;
	d->settings.tex_size = d->settings.tex_sizes[step_tex];
	step = (int)((1.0f - d->menu.slider[2].value)
			* (d->settings.nb_renders - 1) + 0.5f);
	if (step < 0)
		step = 0;
	if (step >= d->settings.nb_renders)
		step = d->settings.nb_renders - 1;
	d->settings.render.width = d->settings.renders[step].width;
	d->settings.render.height = d->settings.renders[step].height;
	d->settings.scale.x = d->settings.display.width / d->settings.render.width;
	d->settings.scale.y = d->settings.display.height
		/ d->settings.render.height;
}

static void	change_slider_settings(t_data *d, t_vector percent, t_slider *s)
{
	t_hitbox		ball_hit;

	ball_hit = (t_hitbox){
		.left = (float)s->ball->instances[0].x
		/ d->settings.screen.width * 100.0f,
		.right = (float)(s->ball->instances[0].x + s->ball->width)
		/ d->settings.screen.width * 100.0f,
		.top = (float)s->ball->instances[0].y
		/ d->settings.screen.height * 100.0f,
		.bot = (float)(s->ball->instances[0].y + s->ball->height)
		/ d->settings.screen.height * 100.0f,
	};
	if (is_inside(ball_hit, percent))
		s->held = true;
}

void	handle_slider_settings(t_data *d, t_vectori mouse)
{
	t_vector const	percent = {.x = (double)mouse.x / d->settings.screen.width
		* 100.0, .y = (double)mouse.y / d->settings.screen.height * 100.0
	};
	t_slider		*s;
	int				bar_l;
	int				bar_r;
	int				i;

	i = -1;
	while (++i < 3)
	{
		s = &d->menu.slider[i];
		bar_l = d->settings.screen.width * (s->bar.left / 100.0f);
		bar_r = d->settings.screen.width * (s->bar.right / 100.0f);
		if (is_inside(s->bar, percent))
		{
			if (mouse.x < bar_l)
				mouse.x = bar_l;
			if (mouse.x > bar_r)
				mouse.x = bar_r;
			s->ball->instances[0].x = mouse.x - s->ball->width / 2;
			s->value = (float)(mouse.x - bar_l) / (bar_r - bar_l);
		}
		change_slider_settings(d, percent, s);
	}
}

void	handle_button_settings(t_data *d, t_vectori mouse)
{
	t_vector const	percent = {
		.x = (double)mouse.x / d->settings.screen.width * 100.0,
		.y = (double)mouse.y / d->settings.screen.height * 100.0
	};

	if (is_inside(d->menu.button[0].hitbox, percent))
	{
		d->settings.map_visible = !d->settings.map_visible;
		update_menu_instances(d);
		return ;
	}
	if (is_inside(d->menu.button[1].hitbox, percent))
	{
		d->settings.fps_visible = !d->settings.fps_visible;
		update_menu_instances(d);
		return ;
	}
	handle_slider_settings(d, mouse);
}
