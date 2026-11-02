/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:38:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 09:05:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	count_objs(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	i;

	i = 0;
	while (i < map->width * map->height)
	{
		y = i / map->width;
		x = i % map->width;
		if (map->grid[y][x] == EMPTY)
			map->count.empty++;
		else if (map->grid[y][x] == WALL)
			map->count.walls++;
		else if (map->grid[y][x] == COLLECTIBLE)
			map->count.collectibles++;
		else if (map->grid[y][x] == FAILED)
			map->count.failed++;
		else if (map->grid[y][x] == PLAYER)
			map->count.player++;
		else if (map->grid[y][x] == EXIT)
			map->count.exit++;
		else if (map->grid[y][x] == BLACK_HOLE)
			map->count.black_hole++;
		i++;
	}
}

static bool	is_valid_items(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	i;

	i = 0;
	while (i < map->width * map->height)
	{
		y = i / map->width;
		x = i % map->width;
		if ((y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
			&& map->grid[y][x] != WALL)
			return (false);
		else if (map->grid[y][x] != EMPTY
			&& map->grid[y][x] != WALL
			&& map->grid[y][x] != COLLECTIBLE
			&& map->grid[y][x] != FAILED
			&& map->grid[y][x] != EXIT
			&& map->grid[y][x] != PLAYER
			&& map->grid[y][x] != BLACK_HOLE)
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_map(t_map *map)
{
	count_objs(map);
	if (map->count.collectibles <= 0 || map->count.player != 1
		|| map->count.exit != 1 || map->count.black_hole > 1)
		return (false);
	else if (!is_valid_items(map) || !check_path(map))
		return (false);
	return (true);
}
