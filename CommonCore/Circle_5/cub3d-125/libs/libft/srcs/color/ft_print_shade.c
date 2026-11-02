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

#ifdef COLOR_ON

static t_rgb	ft_hex_to_rgb(uint32_t hex)
{
	t_rgb	color;

	color.r = (hex >> 16) & 0xFF;
	color.g = (hex >> 8) & 0xFF;
	color.b = hex & 0xFF;
	return (color);
}

void	ft_print_shade(const char *str, uint32_t start_hex, uint32_t end_hex)
{
	t_rgb	start;
	t_rgb	end;
	size_t	len;
	size_t	i;
	double	ratio;

	start = ft_hex_to_rgb(start_hex);
	end = ft_hex_to_rgb(end_hex);
	len = ft_strlen(str);
	if (len == 0)
		return ;
	i = 0;
	while (i < len)
	{
		ratio = (double)i / (len - 1);
		ft_printf("\033[38;2;%d;%d;%dm%c",
			(uint8_t)(start.r + ratio * (end.r - start.r)),
			(uint8_t)(start.g + ratio * (end.g - start.g)),
			(uint8_t)(start.b + ratio * (end.b - start.b)), str[i++]);
	}
	ft_reset_color();
}

#else

void	ft_print_shade(const char *str, uint32_t start_hex, uint32_t end_hex)
{
	(void)start_hex;
	(void)end_hex;
	ft_putstr(str);
}

#endif
