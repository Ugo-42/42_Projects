/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:13:29 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/10 11:15:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	get_player_pos(t_data *d)
{
	return ((t_vector){
		(d->player.x + (d->image.player->width / 2)) / d->settings.tile_size,
		(d->player.y + (d->image.player->height / 2)) / d->settings.tile_size
	});
}

t_vector	get_ray_dir(double angle, double camera_x)
{
	return ((t_vector){
		cos(angle) + (-sin(angle) * tan(FOV * M_PI / 360)) * camera_x,
		sin(angle) + (cos(angle) * tan(FOV * M_PI / 360)) * camera_x
	});
}

t_vector	get_delta_dist(t_vector ray_dir)
{
	return ((t_vector){
		fabs(1.0 / fmax(fabs(ray_dir.x), 1e-30)),
		fabs(1.0 / fmax(fabs(ray_dir.y), 1e-30))
	});
}
