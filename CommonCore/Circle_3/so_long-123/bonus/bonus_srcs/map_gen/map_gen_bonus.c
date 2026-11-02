/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:19:33 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 14:16:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	generate_maze(t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->grid[y][x] = WALL;
			map->wall_count++;
			x++;
		}
		y++;
	}
	map->grid[1][1] = EMPTY;
	map->wall_count++;
	carve_passages(map, 1, 1);
}

static void	place_exit(t_map *map)
{
	size_t	x;
	size_t	y;

	while (1)
	{
		x = rand() % (map->width - 2) + 1;
		y = rand() % (map->height - 2) + 1;
		if (map->grid[y][x] == EMPTY && (abs((int)x - 1)
			+ abs((int)y - 1) >= (int)map->width / 4))
		{
			map->grid[y][x] = EXIT;
			break ;
		}
	}
}

static void	place_collectibles(t_map *map, int density)
{
	size_t	x;
	size_t	y;
	size_t	i;
	size_t	collectible_count;

	collectible_count
		= ((map->width * map->height - map->wall_count) * density) / 100;
	i = 0;
	if (collectible_count == 0)
		collectible_count = 1;
	while (i < collectible_count)
	{
		x = rand() % (map->width - 2) + 1;
		y = rand() % (map->height - 2) + 1;
		if (map->grid[y][x] == EMPTY)
		{
			map->grid[y][x] = COLLECTIBLE;
			i++;
		}
	}
}

static void	place_objects(t_map *map, int density)
{
	map->grid[1][1] = PLAYER;
	place_exit(map);
	place_collectibles(map, density);
}

void	map_gen(t_map *map, int density)
{
	map->wall_count = 0;
	map->grid = ft_malloc_2d(map->height, map->width, sizeof(t_objs));
	if (!map->grid)
		ft_exit_error(1, "In 'ft_generate_random_map': " BAD_ALLOC);
	generate_maze(map);
	place_objects(map, density);
}
