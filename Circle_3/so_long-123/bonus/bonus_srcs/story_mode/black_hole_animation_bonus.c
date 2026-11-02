/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_hole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:27:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 13:27:35 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animate_black_hole(t_data *data, size_t rotation)
{
	size_t	i;
	size_t	layer;
	size_t	angle;
	size_t	left_rotation;

	i = 0;
	while (i < 2 * 8)
	{
		layer = i / 8;
		angle = i % 8;
		data->black_hole.bh[layer][angle]->instances->enabled = false;
		i++;
	}
	left_rotation = (8 - rotation % 8) % 8;
	if (data->black_hole.speed > 0)
		data->black_hole.bh[0][left_rotation]->instances->enabled = true;
	if (data->black_hole.speed > 50)
		data->black_hole.bh[1][rotation % 8]->instances->enabled = true;
}
