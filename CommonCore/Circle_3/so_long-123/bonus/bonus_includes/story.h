/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endless.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/06 11:23:46 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STORY_H
# define STORY_H

# include "so_long_bonus.h"

/* Story Map Paths */
# define STORY_MAP_1 "ber.d/story/story1.ber"
# define STORY_MAP_2 "ber.d/story/story2.ber"
# define STORY_MAP_3 "ber.d/story/story3.ber"

/* Story TexTures Paths */
# define STTP_PLAYER "./sprites/story/character.png"
# define STTP_WALL "./sprites/story/wall.png"
# define STTP_SUCCESS "./sprites/story/success.png"
# define STTP_FAILED "./sprites/story/failed.png"
# define STTP_EXIT "./sprites/story/exit.png"
# define STTP_EMPTY "./sprites/story/background.png"

/* FUNCTIONS */
void	animate_black_hole(t_data *data, size_t rotation);
void	init_black_hole(t_data *data);
void	so_story(t_data *data);
void	story_checks(t_data *data);

/* Hooks */
void	black_hole(void *param);

#endif
