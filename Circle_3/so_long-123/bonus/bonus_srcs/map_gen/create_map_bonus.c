/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:41:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 10:39:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*create_map(size_t width, size_t height, size_t density)
{
	char	*filename;
	t_map	map;

	filename = ".tmp.ber";
	map.width = width;
	if (map.width % 2 == 0)
		map.width--;
	map.height = height;
	if (map.height % 2 == 0)
		map.height--;
	if (map.width < 5 || map.height < 5)
		ft_exit_error(1, "Map size is too small");
	if (map.width > 800 || map.height > 800)
		ft_exit_error(1, "Map size is too large");
	map_gen(&map, density);
	save_map_to_file(&map, filename);
	ft_free_2d_array((void ***)&map.grid, map.height);
	return (filename);
}
