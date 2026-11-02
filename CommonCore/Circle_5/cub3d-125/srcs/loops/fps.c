/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:30:53 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/26 22:34:35 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_fps(void *data)
{
	t_fps			*fps;
	struct timeval	now;

	fps = &((t_data *)data)->fps;
	gettimeofday(&now, NULL);
	fps->delta_time = (now.tv_sec - fps->last_time.tv_sec) * 1000
		+ (now.tv_usec - fps->last_time.tv_usec) / 1000.0;
	fps->last_time = now;
	fps->accumulated_time += fps->delta_time;
	fps->frame_count++;
	if (fps->accumulated_time >= FPS_UPDATE_MS)
	{
		fps->fps = fps->frame_count * 1000.0 / fps->accumulated_time;
		fps->frame_count = 0;
		fps->accumulated_time = 0.0;
		print_fps(data);
	}
}
