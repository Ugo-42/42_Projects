/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/04 10:58:47 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42.h"
# include "color.h"

# include "sl_structs.h"
# include <fcntl.h>

/* the maximum number
   of tiles of a map */
# define MAX_WIDTH 64
# define MAX_HEIGHT 64

/* the maximum percentage that
   the window will occupate */
# define SIZE_PERCENTAGE 90

/* the TexTures Paths */
# define TTP_PLAYER "./sprites/minecraft/character.png"
# define TTP_WALL "./sprites/minecraft/wall.png"
# define TTP_COLLECTIBLE "./sprites/minecraft/collectible.png"
# define TTP_EXIT "./sprites/minecraft/exit.png"
# define TTP_EMPTY "./sprites/minecraft/background.png"

/* FUNCTIONS */
bool	check_path(t_map *map);
bool	is_valid_map(t_map *map);

void	center_window(t_data data);
void	cleanup(void *param);
void	init_sprites(t_data *data);
void	keyinput(mlx_key_data_t keydata, void *param);
void	read_ber_file(t_data *data, char *ber);
void	resize_window(t_data *data);
void	so_long(char *ber);

#endif
