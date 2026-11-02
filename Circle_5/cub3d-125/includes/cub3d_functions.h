/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:52:28 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/25 15:48:18 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_FUNCTIONS_H
# define CUB3D_FUNCTIONS_H

# include "MLX42.h"
# include "cub3d_structs.h"

/* ************************************************************************** */
/*                                  CUB3D                                     */
/* ************************************************************************** */

void			cub3d(t_data *data);

void			handle_menu(t_data *data);
void			reload_textures(t_data *d);
void			update_menu_instances(t_data *d);
void			update_sliders(t_data *d);
void			apply_slider_settings(t_data *d);
void			handle_slider_settings(t_data *d, t_vectori mouse);
void			handle_button_settings(t_data *d, t_vectori mouse);

/* ************************************************************************** */
/*                                  INIT                                      */
/* ************************************************************************** */

bool			init_data(t_data *d);
void			init_menu(t_data *d);
void			init_fps_images(t_data *data);
void			assign_default_assets(t_data *data);
uint32_t		try_color(char *path);
void			load_image(t_data *d, char *path, mlx_image_t **img, int size);
void			set_no_color(t_data *d, mlx_image_t **image,
					int sz_1, int sz_2);
mlx_image_t		*set_color(t_data *d, int sz_1, int sz_2, uint32_t color);
void			load_textures(t_data *data);

/* ************************************************************************** */
/*                                  INPUT                                     */
/* ************************************************************************** */

void			movement(void *param);
void			update_movement(t_data *d);
void			update_rotation(t_data *d);
void			update_rotation_mouse(t_data *d);
void			draw_map(t_data *d);

/* ************************************************************************** */
/*                                  LOOPS                                     */
/* ************************************************************************** */

void			fps_loop(t_data *data);
void			movement_loop(t_data *data);
void			update_fps(void *param);

/* ************************************************************************** */
/*                                 PARSING                                    */
/* ************************************************************************** */

bool			parsing(const char *file, t_data *data);
int				check_map(t_data *data);

/* ************************************************************************** */
/*                               RAY CASTING                                  */
/* ************************************************************************** */

void			clear_render_buffer(t_data *d);
void			push_frame(t_data *d);
void			upscaling(t_data *d);

t_vector		get_delta_dist(t_vector ray_dir);
t_vector		get_player_pos(t_data *d);
t_vector		get_ray_dir(double angle, double camera_x);

void			render_column(t_data *d, t_vectors v, t_dda *dda, int screen_x);

void			draw_view(t_data *data);

/* ************************************************************************** */
/*                                  UTILS                                     */
/* ************************************************************************** */

bool			is_e_key_hit(t_data *d);
bool			is_esc_hit(t_data *d);
bool			is_inside(t_hitbox b, t_vector pos);
bool			is_left_clicked(t_data *d);
bool			is_left_held(t_data *d);
bool			is_moving(t_data *d);
bool			is_valid_path(char const *path);
bool			print_error(const char *msg);
void			center_window(t_data data);
void			cleanup(void *param);
void			clear_image(mlx_image_t *img);
void			print_fps(t_data *data);
void			print_usage(void);
void			resize_window(t_data *data);
unsigned int	ft_atou(const char *str);

#endif
