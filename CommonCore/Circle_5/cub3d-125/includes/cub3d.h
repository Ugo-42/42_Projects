/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:52:28 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/22 14:49:43 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_color.h"
# include "cub3d_functions.h"
# include "cub3d_structs.h"

# include "_benchmark.h"

# include "libft.h"
# include "MLX42.h"

# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

/* maths constants */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif

# define TWO_PI 6.28318530717958647692

# define MP_SIZE 800
# define MP_TILE_SZ 40

/* the maximum percentage that
   the window will occupate */
# define SIZE_PERCENTAGE        100.0f

/* the fps refresh rate in
   milliseconds */
# define FPS_UPDATE_MS          300.0f

/* default field of view */
# define FOV                    80.0f

/* defines the largest usable resolution */
# define MAX_RESOLUTION_WIDTH   3840
# define MAX_RESOLUTION_HEIGHT  2160

/* default resolution for rendering */
# define DEFAULT_RENDER_WIDTH   1920
# define DEFAULT_RENDER_HEIGHT  1080

/* default texture sizes */
# define DEFAULT_TEXTURE_SIZE   1024

# define MAP_COLOR_ON 1

# if MAP_COLOR_ON
#  define DEFAULT_MAP_FG_COLOR  0x444444FF
#  define DEFAULT_MAP_BG_COLOR  0x111111FF
#  define DEFAULT_MAP_DG_COLOR  0xAF502BFF
#  define DEFAULT_VIEW_COLOR    0xFFFFFFFF
# else
#  define DEFAULT_MAP_FG_COLOR  0x00000000
#  define DEFAULT_MAP_BG_COLOR  0x00000000
#  define DEFAULT_VIEW_COLOR    0x00000000
# endif

#endif
