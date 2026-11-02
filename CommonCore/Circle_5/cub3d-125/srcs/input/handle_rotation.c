/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:13:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/13 14:29:16 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                 ROTATION                                   */
/* ************************************************************************** */

/**
 * @brief Wraps an angle to the range [0, 2π].
 * @return The wrapped angle in radians.
 */
static inline float	wrap_angle(float angle)
{
	angle = fmodf(angle, TWO_PI);
	if (angle < 0.0f)
		return (angle + TWO_PI);
	return (angle);
}

/* Mouse */
void	update_rotation_mouse(t_data *d)
{
	t_vectori const	center = {
		d->settings.screen.width / 2,
		d->settings.screen.height / 2
	};
	int32_t			x;
	int32_t			y;
	double			delta_x;

	mlx_get_mouse_pos(d->mlx, &x, &y);
	delta_x = (x - center.x);
	d->player.angle = wrap_angle(d->player.angle + delta_x
			* ((d->settings.rotation_speed / 49) * d->fps.delta_time));
	d->mouse_movement = (delta_x != 0);
	mlx_set_mouse_pos(d->mlx, center.x, center.y);
}

/* Arrows */
void	update_rotation(t_data *d)
{
	float const	speed = d->settings.rotation_speed * d->fps.delta_time;

	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		d->player.angle = wrap_angle(d->player.angle - speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		d->player.angle = wrap_angle(d->player.angle + speed);
}
