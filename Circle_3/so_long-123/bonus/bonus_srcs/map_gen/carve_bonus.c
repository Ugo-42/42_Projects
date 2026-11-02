/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:34:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 14:16:41 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	shuffle_directions(t_rdfs *directions)
{
	size_t	i;
	size_t	j;
	t_rdfs	temp;

	i = 0;
	while (i < 4)
	{
		j = rand() % 4;
		temp = directions[i];
		directions[i++] = directions[j];
		directions[j] = temp;
	}
}

static void	init_dir(t_rdfs *directions)
{
	directions[0].x = 1;
	directions[0].y = 0;
	directions[1].x = -1;
	directions[1].y = 0;
	directions[2].x = 0;
	directions[2].y = 1;
	directions[3].x = 0;
	directions[3].y = -1;
}

void	carve_passages(t_map *map, int x, int y)
{
	size_t	i;
	size_t	nx;
	size_t	ny;
	t_rdfs	directions[4];

	init_dir(directions);
	shuffle_directions(directions);
	i = 0;
	while (i < 4)
	{
		nx = x + directions[i].x * 2;
		ny = y + directions[i].y * 2;
		if (nx > 0 && nx < map->width - 1 && ny > 0 && ny < map->height - 1
			&& map->grid[ny][nx] == WALL)
		{
			map->grid[ny - directions[i].y][nx - directions[i].x] = EMPTY;
			map->grid[ny][nx] = EMPTY;
			map->wall_count -= 2;
			carve_passages(map, nx, ny);
		}
		i++;
	}
}
