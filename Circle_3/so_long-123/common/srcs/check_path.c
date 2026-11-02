/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:42:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/03 13:15:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(t_map *map, int **visited, int x, int y)
{
	if (x < 0 || x >= (int)map->width || y < 0 || y >= (int)map->height)
		return ;
	if (map->grid[y][x] == WALL || visited[y][x])
		return ;
	visited[y][x] = 1;
	flood_fill(map, visited, x + 1, y);
	flood_fill(map, visited, x - 1, y);
	flood_fill(map, visited, x, y + 1);
	flood_fill(map, visited, x, y - 1);
}

/* Finds the player's starting position and initiates flood fill */
static void	start_flood_fill(t_map *map, int **visited)
{
	size_t	i;
	int		x;
	int		y;

	i = 0;
	while (i < map->width * map->height)
	{
		y = i / map->width;
		x = i % map->width;
		if (map->grid[y][x] == PLAYER)
		{
			flood_fill(map, visited, x, y);
			return ;
		}
		i++;
	}
}

/* Checks if all exits and collectibles are reachable */
static bool	is_valid_path(t_map *map, int **visited)
{
	size_t	i;
	size_t	x;
	size_t	y;
	bool	valid;

	valid = true;
	i = 0;
	while (i < map->width * map->height)
	{
		y = i / map->width;
		x = i % map->width;
		if ((map->grid[y][x] == EXIT || map->grid[y][x] == COLLECTIBLE)
			&& !visited[y][x])
			valid = false;
		i++;
	}
	ft_free_2d_array((void ***)&visited, map->height);
	return (valid);
}

bool	check_path(t_map *map)
{
	int	**visited;

	visited = ft_calloc_2d(map->height, map->width, sizeof(int));
	if (!visited)
		return (false);
	start_flood_fill(map, visited);
	return (is_valid_path(map, visited));
}
