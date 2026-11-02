/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darken_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:36:04 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/03 11:00:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_brighten_color(uint32_t hex_color, int percentage)
{
	const float	factor = (100 + percentage) / 100.0f;
	long		r;
	long		g;
	long		b;

	r = ((hex_color >> 16) & 0xFF) * factor;
	g = ((hex_color >> 8) & 0xFF) * factor;
	b = (hex_color & 0xFF) * factor;
	ft_normalize(&r, 0, 255);
	ft_normalize(&g, 0, 255);
	ft_normalize(&b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}
