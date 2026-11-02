/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_black_hole.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:37:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 09:04:57 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_failed(t_data *data)
{
	mlx_instance_t	*player;
	mlx_instance_t	*failed;
	size_t			i;

	player = data->sprites.player->instances;
	failed = data->sprites.failed->instances;
	i = 0;
	while (i < data->sprites.failed->count)
	{
		if (player->x == failed[i].x && player->y == failed[i].y
			&& failed[i].enabled)
		{
			failed[i].enabled = false;
			data->map.count.failed--;
			data->days -= rand() % 25;
			if (data->days < 0)
				data->days = 0;
		}
		i++;
	}
}

static void	check_success(t_data *data)
{
	mlx_instance_t	*player;
	mlx_instance_t	*success;
	size_t			i;

	player = data->sprites.player->instances;
	success = data->sprites.collectibles->instances;
	i = 0;
	while (i < data->sprites.collectibles->count)
	{
		if (player->x == success[i].x && player->y == success[i].y
			&& success[i].enabled)
		{
			success[i].enabled = false;
			data->map.count.collectibles--;
			data->days += rand() % 10;
			if (data->days > 100)
				data->days = 100;
		}
		i++;
	}
}

void	story_checks(t_data *data)
{
	check_success(data);
	check_failed(data);
}
