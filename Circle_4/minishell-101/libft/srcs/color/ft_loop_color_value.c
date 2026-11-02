/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/14 15:08:19 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_loop_color_value(void)
{
	static t_rgb	color = {255, 0, 0};
	static int32_t	step = 1;

	if (step == 1)
		color.g += 15;
	if (step == 2)
		color.r -= 15;
	if (step == 3)
		color.b += 15;
	if (step == 4)
		color.g -= 15;
	if (step == 5)
		color.r += 15;
	if (step == 6)
		color.b -= 15;
	if ((step == 1 && color.g >= 255) || (step == 2 && color.r <= 0)
		|| (step == 3 && color.b >= 255) || (step == 4 && color.g <= 0)
		|| (step == 5 && color.r >= 255) || (step == 6 && color.b <= 0))
		step = (step % 6) + 1;
	return ((color.r << 16) | (color.g << 8) | color.b);
}
