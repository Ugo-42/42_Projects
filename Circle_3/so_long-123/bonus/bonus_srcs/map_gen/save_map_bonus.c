/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:19:33 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/06 11:50:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	save_map_to_file(t_map *map, const char *filename)
{
	FILE	*file;
	size_t	y;
	size_t	x;

	y = 0;
	file = fopen(filename, "w");
	if (!file)
	{
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			fputc(map->grid[y][x++], file);
		}
		fputc('\n', file);
		y++;
	}
	fclose(file);
}
