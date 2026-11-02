/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 13:47:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "MLX42.h"
# include "color.h"

# include "sl_structs_bonus.h"
# include "map_gen.h"
# include "endless.h"
# include "story.h"
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
void	handle_options(t_data *data, char **map_path, int argc, char **argv);
void	init_data(t_data *data, char *ber);
void	init_sprites(t_data *data);
void	print_moves(t_data *data, char *text);
void	print_days(t_data *data, char *text, uint32_t color_hex, bool smooth);
void	read_ber_file(t_data *data, char *ber);
void	resize_window(t_data *data);
void	so_long(t_data *data, char *ber);

/* Hooks */
void	keyinput(mlx_key_data_t keydata, void *param);

#endif
