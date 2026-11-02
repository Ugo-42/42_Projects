/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:50:28 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/04 14:37:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_data(t_data *data, char *ber)
{
	t_objs_count	*c;

	c = &data->map.count;
	ft_ultimate_bzero("6zu,2p", &c->empty, &c->walls, &c->collectibles,
		&c->exit, &c->player, &data->moves, &data->mlx, &data->map.grid);
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

void	so_long(char *ber)
{
	t_data	data;

	init_data(&data, ber);
	init_sprites(&data);
	mlx_key_hook(data.mlx, keyinput, &data);
	mlx_loop(data.mlx);
	cleanup((void *)&data);
}
