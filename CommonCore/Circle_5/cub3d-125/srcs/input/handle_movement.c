/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:13:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 13:53:39 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                COLLISION                                   */
/* ************************************************************************** */

static inline bool	is_wall(t_data *d, float x, float y)
{
	int const	ts = d->settings.tile_size;

	if (d->settings.door_close && d->map.map[(int)y / ts][(int)x / ts] == 'D')
		return (true);
	return (d->map.map[(int)y / ts][(int)x / ts] == '1');
}

static inline bool	is_collision(t_data *d, float x, float y)
{
	float const	w = d->image.player->width;
	float const	h = d->image.player->height;

	return (is_wall(d, x + w, y + h) || is_wall(d, x, y + h)
		|| is_wall(d, x + w, y) || is_wall(d, x, y));
}

/* ************************************************************************** */
/*                                MOVEMENT                                    */
/* ************************************************************************** */

#define MIN_MOVE 0.1f

static inline void	try_move(t_data *d, float dx, float dy, float speed)
{
	float const	new_x = d->player.x + (dx * speed);
	float const	new_y = d->player.y + (dy * speed);

	if (speed < MIN_MOVE)
		return ;
	if (!is_collision(d, new_x, d->player.y))
		d->player.x = new_x;
	if (!is_collision(d, d->player.x, new_y))
		d->player.y = new_y;
	if (is_collision(d, d->player.x, new_y)
		|| is_collision(d, new_x, d->player.y))
		try_move(d, dx, dy, speed / 2);
}

void	update_movement(t_data *d)
{
	float const	a = d->player.angle;
	float const	strafe_a = a + M_PI_2;
	float		speed;

	speed = d->settings.movement_speed * d->fps.delta_time;
	if (speed > 50.0f)
		speed = 50.0f;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
		try_move(d, cosf(a), sinf(a), speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
		try_move(d, -cosf(a), -sinf(a), speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
		try_move(d, -cosf(strafe_a), -sinf(strafe_a), speed);
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
		try_move(d, cosf(strafe_a), sinf(strafe_a), speed);
}
