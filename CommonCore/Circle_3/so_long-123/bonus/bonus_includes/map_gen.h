/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:16:27 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/06 11:41:02 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GEN_H
# define MAP_GEN_H

/* Personal libs */
# include "libft.h"
# include "struct.h"
# include "color.h"
# include "so_long_bonus.h"

/* Standard libs */
# include <fcntl.h>
# include <time.h>
# include <stdio.h>

typedef struct s_rdfs
{
	size_t		x;
	size_t		y;
}	t_rdfs;

char	*create_map(size_t width, size_t height, size_t density);
void	carve_passages(t_map *map, int x, int y);
void	map_gen(t_map *map, int density);
void	save_map_to_file(t_map *map, const char *filename);

#endif
