/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:50:28 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 14:09:21 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_data(t_data *data, char *ber)
{
	t_objs_count	*c;

	c = &data->map.count;
	ft_ultimate_bzero("9zu,4p,2d", &c->empty, &c->walls, &c->collectibles,
		&c->failed, &c->exit, &c->player, &c->black_hole, &data->moves,
		&data->black_hole.speed, &data->mlx, &data->map.grid,
		&data->moves_text, &data->days_text,
		&data->black_hole.bh_update, &data->black_hole.days_update);
	data->ber_file_fd = -1;
	read_ber_file(data, ber);
	if (!is_valid_map(&data->map))
	{
		ft_cexit_error(1, "Invalid map.", cleanup, data);
	}
	data->mlx = mlx_init(1600, 900, "So_long", false);
	if (!data->mlx)
	{
		ft_cexit_error(42, "In 'init_data': Error launching mlx.",
			cleanup, data);
	}
	resize_window(data);
	center_window(*data);
}

void	so_long(t_data *data, char *ber)
{
	init_data(data, ber);
	init_sprites(data);
	print_moves(data, ft_strdup("Moves: 0"));
	if (data->endless)
	{
		print_days(data, ft_stringf("days: %d", data->days),
			loop_color_value(), true);
	}
	if (data->story)
	{
		print_days(data, ft_stringf("%d days left until blackhole absorption",
				data->days), 0xFFFFFF, true);
	}
	mlx_key_hook(data->mlx, keyinput, data);
	if (data->map.count.black_hole)
		mlx_loop_hook(data->mlx, black_hole, data);
	mlx_loop(data->mlx);
	cleanup(data);
}
