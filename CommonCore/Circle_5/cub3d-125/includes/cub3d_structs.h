/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:52:28 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/22 15:29:31 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <stddef.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                                RAY CASTING                                 */
/* ************************************************************************** */

typedef struct s_draw
{
	int				start;
	int				end;
	uint8_t			*px;
	uint32_t		*dst;
	uint32_t		color;
	double			wall_start;
}	t_draw;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_vectori
{
	int	x;
	int	y;
}	t_vectori;

typedef struct s_vectors
{
	t_vector	delta;
	t_vector	pos;
	t_vector	ray_dir;
	t_vector	side;
	t_vectori	map;
	t_vectori	step;
}	t_vectors;

typedef struct s_dda
{
	bool	side_hit;
	double	perp_dist;
	int		line_height;
	double	wall_x;
	int		tex_x;
	int		tex_y;
}	t_dda;

typedef struct s_frame_buffers
{
	uint32_t	*frame;
	uint32_t	*render;
}	t_frame_buffers;

/* ************************************************************************** */
/*                                 RENDERING                                  */
/* ************************************************************************** */

typedef struct s_image
{
	mlx_image_t	*player;
	mlx_image_t	*no_image;
	mlx_image_t	*so_image;
	mlx_image_t	*ea_image;
	mlx_image_t	*we_image;
	mlx_image_t	*d_image;
	mlx_image_t	*f_image;
	mlx_image_t	*c_image;
	mlx_image_t	*w_square;
	mlx_image_t	*f_square;
	mlx_image_t	*d_square;
	mlx_image_t	*view;
	mlx_image_t	*view_map;
	mlx_image_t	*mini_map;
	mlx_image_t	*mp_player;
}	t_image;

typedef struct s_assets
{
	char	*player;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*f_path;
	char	*c_path;
}	t_assets;

/* ************************************************************************** */
/*                                PLAYER / MAP                                */
/* ************************************************************************** */

typedef struct s_player
{
	float		x;
	float		y;
	int			map_x;
	int			map_y;
	float		angle;
	char		view;
}	t_player;

typedef struct s_map
{
	char		**map;
	int			*len;
	int			width;
	int			height;
	size_t		size;
}	t_map;

typedef struct s_mini_map
{
	int			map_x;
	int			map_y;
	float		mn_x;
	float		mn_y;
	float		offset_x;
	float		offset_y;
}	t_mini_map;

/* ************************************************************************** */
/*                                   TIMING                                   */
/* ************************************************************************** */

typedef struct s_fps
{
	mlx_image_t		*fps_img[61];
	struct timeval	last_time;
	int				fps;
	int				frame_count;
	double			accumulated_time;
	double			delta_time;
}	t_fps;

/* ************************************************************************** */
/*                                    MENU                                    */
/* ************************************************************************** */

typedef enum e_state
{
	M_NONE,
	M_MAIN,
	M_SETTINGS,
}	t_state;

typedef struct s_hitbox
{
	float	left;
	float	right;
	float	top;
	float	bot;
}	t_hitbox;

typedef struct s_img_config
{
	mlx_image_t	**img;
	char		*path;
	t_vectori	origin_size;
	t_vector	percent;
	float		scale_divisor;
}	t_img_config;

typedef struct s_button
{
	mlx_image_t	*on;
	mlx_image_t	*off;
	t_hitbox	hitbox;
}	t_button;

typedef struct s_slider
{
	mlx_image_t	*ball;
	mlx_image_t	*bar_bg;
	t_hitbox	bar;
	float		value;
	bool		held;
}	t_slider;

typedef struct s_menu
{
	mlx_image_t	*main;
	mlx_image_t	*settings;
	mlx_image_t	*settings_bg;
	t_button	button[2];
	t_slider	slider[3];
	t_state		state;
	bool		enabled;
	bool		init_success;
}	t_menu;

/* ************************************************************************** */
/*                                    MAIN                                    */
/* ************************************************************************** */

typedef struct s_resolution
{
	int	width;
	int	height;
}	t_resolution;

typedef struct s_settings
{
	int				tile_size;
	int				fov;
	float			movement_speed;
	float			rotation_speed;
	t_resolution	screen;
	t_resolution	display;
	t_resolution	render;
	t_resolution	renders[32];
	int				nb_renders;
	int				curr_tex_size;
	int				tex_size;
	int				tex_sizes[32];
	int				nb_tex_sizes;
	t_vectori		scale;
	uint32_t		view_color;
	uint32_t		map_fg;
	uint32_t		map_bg;
	uint32_t		map_dg;
	bool			map_visible;
	bool			fps_visible;
	bool			door_close;
}	t_settings;

typedef struct s_data
{
	t_frame_buffers	buf;
	t_assets		assets;
	t_image			image;
	t_map			map;
	t_player		player;
	mlx_t			*mlx;
	t_settings		settings;
	t_fps			fps;
	t_menu			menu;
	t_mini_map		mmap;
	bool			mouse_movement;
}	t_data;

#endif
