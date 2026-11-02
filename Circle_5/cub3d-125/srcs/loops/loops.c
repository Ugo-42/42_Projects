/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:44 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/13 13:55:33 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, &movement, data);
}

void	fps_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, &update_fps, data);
}
