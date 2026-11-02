/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_hole_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:27:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/10 09:31:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_loose(t_data *data)
{
	mlx_instance_t	*player;
	mlx_instance_t	*black_hole;

	player = data->sprites.player->instances;
	black_hole = data->black_hole.immobile->instances;
	if (player->x < black_hole->x + 50 && player->x > black_hole->x - 50
		&& player->y < black_hole->y + 50 && player->y > black_hole->y - 50)
	{
		data->story = false;
		mlx_close_window(data->mlx);
	}
}

static void	move_animated_bh(t_data *data, int bh_x, int bh_y)
{
	size_t	layer;
	size_t	angle;
	size_t	i;

	i = 0;
	while (i < 2 * 8)
	{
		layer = i / 8;
		angle = i % 8;
		data->black_hole.bh[layer][angle]->instances->x = bh_x;
		data->black_hole.bh[layer][angle]->instances->y = bh_y;
		i++;
	}
}

static void	move_black_hole(t_data *data)
{
	mlx_instance_t	*player;
	mlx_instance_t	*immobile_bh;
	int				dx;
	int				dy;

	player = data->sprites.player->instances;
	immobile_bh = data->black_hole.immobile->instances;
	dx = player->x - immobile_bh->x;
	dy = player->y - immobile_bh->y;
	if (dx != 0)
		dx /= abs(dx);
	if (dy != 0)
		dy /= abs(dy);
	immobile_bh->x += dx * 9;
	immobile_bh->y += dy * 9;
	move_animated_bh(data, immobile_bh->x, immobile_bh->y);
}

static void	print_days_story(t_data *data)
{
	if (data->days > 30)
	{
		print_days(data, ft_stringf("%d days left until blackhole absorption",
				data->days), 0xFFFFFF, true);
	}
	else if (data->days > 10)
	{
		print_days(data, ft_stringf("%d days left until blackhole absorption",
				data->days), 0xFF0000, true);
	}
	else
	{
		print_days(data, ft_stringf("%d days left until blackhole absorption",
				data->days), 0xFF0000, false);
	}
}

void	black_hole(void *param)
{
	t_data			*data;
	static size_t	rotation;
	double			current_time;
	double			delay;

	data = param;
	current_time = mlx_get_time();
	data->black_hole.speed = 100 - data->days;
	delay = 0.1 - (0.09 * data->black_hole.speed / 100);
	if (current_time - data->black_hole.days_update >= 1.0)
	{
		data->days--;
		if (data->days < 0)
			data->days = 0;
		data->black_hole.days_update = current_time;
	}
	if (current_time - data->black_hole.bh_update >= delay)
	{
		print_days_story(data);
		data->black_hole.bh_update = current_time;
		animate_black_hole(data, rotation++);
		if (data->black_hole.speed > 0)
			move_black_hole(data);
		check_loose(data);
	}
}
