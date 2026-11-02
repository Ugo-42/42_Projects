/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:19:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 11:54:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_esc_hit(t_data *d)
{
	static bool	prev_state = false;
	const bool	curr_state = mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE);
	const bool	pressed_once = (curr_state && !prev_state);

	prev_state = curr_state;
	return (pressed_once);
}

bool	is_e_key_hit(t_data *d)
{
	static bool	prev_state = false;
	const bool	curr_state = mlx_is_key_down(d->mlx, MLX_KEY_E);
	const bool	pressed_once = (curr_state && !prev_state);

	prev_state = curr_state;
	return (pressed_once);
}

bool	is_left_clicked(t_data *d)
{
	static bool	prev_state = false;
	const bool	curr_state = mlx_is_mouse_down(d->mlx, MLX_MOUSE_BUTTON_LEFT);
	const bool	clicked_once = (curr_state && !prev_state);

	prev_state = curr_state;
	return (clicked_once);
}

bool	is_left_held(t_data *d)
{
	return (mlx_is_mouse_down(d->mlx, MLX_MOUSE_BUTTON_LEFT));
}

bool	is_moving(t_data *d)
{
	if (mlx_is_key_down(d->mlx, MLX_KEY_W)
		|| mlx_is_key_down(d->mlx, MLX_KEY_S)
		|| mlx_is_key_down(d->mlx, MLX_KEY_A)
		|| mlx_is_key_down(d->mlx, MLX_KEY_D)
		|| mlx_is_key_down(d->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(d->mlx, MLX_KEY_RIGHT)
		|| d->mouse_movement)
		return (true);
	return (false);
}
