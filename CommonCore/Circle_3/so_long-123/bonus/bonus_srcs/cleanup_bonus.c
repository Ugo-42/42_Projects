/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:21:26 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 14:24:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	cleanup(void *param)
{
	t_data	*data;

	data = param;
	if (data->ber_file_fd >= 0)
	{
		close(data->ber_file_fd);
		data->ber_file_fd = -1;
	}
	if (data->map.grid)
		ft_free_2d_array((void ***)&data->map.grid, data->map.height);
	if (data->mlx)
	{
		mlx_terminate(data->mlx);
		data->mlx = NULL;
	}
	unlink(".tmp.ber");
}
