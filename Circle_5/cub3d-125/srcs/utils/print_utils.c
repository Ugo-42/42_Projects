/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:05:42 by vvalenti          #+#    #+#             */
/*   Updated: 2025/08/22 10:14:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	print_error(const char *msg)
{
	ft_putstr_fd(2, BOLD RED "Error\n" RESET);
	ft_putstr_nl_fd(2, msg);
	return (false);
}

void	print_fps(t_data *d)
{
	static int	last_fps;
	static bool	was_visible;

	if (!d->settings.fps_visible)
	{
		if (was_visible)
			d->fps.fps_img[last_fps]->enabled = false;
		was_visible = false;
		return ;
	}
	if (d->fps.fps < 0)
		d->fps.fps = 0;
	if (d->fps.fps > 60)
		d->fps.fps = 60;
	if (!was_visible)
		d->fps.fps_img[d->fps.fps]->enabled = true;
	if (d->fps.fps != last_fps)
	{
		d->fps.fps_img[last_fps]->enabled = false;
		d->fps.fps_img[d->fps.fps]->enabled = true;
		last_fps = d->fps.fps;
	}
	was_visible = true;
}

#define A GRAYISH_BLUE
#define B LIGHT_BLUE
#define C WHITE_BLUE

void	print_usage(void)
{
	ft_putstr(
		BOLD A
		"╭───────────────────────────────────╮\n"
		"│" B "               cub3D               " A "│\n"
		"╰───────────────────────────────────╯\n"
		RESET C
		"Usage: ./cub3d <map.cub>\n"
		RESET \
	);
}
