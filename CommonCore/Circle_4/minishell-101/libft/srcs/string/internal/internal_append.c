/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:38:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 11:38:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	internal_append_ptr(t_flexistr *fs, uintptr_t addr)
{
	if (!addr)
		fs_append(fs, "(nil)", false);
	else
	{
		fs_append(fs, "0x", false);
		fs_append_nb(fs, addr, "0123456789abcdef");
		if (fs->errnum == 0)
			fs->last_append_len += 2;
	}
}

void	internal_append_str(t_flexistr *fs, char *s)
{
	if (!s)
		fs_append(fs, "(null)", false);
	else
		fs_append(fs, s, false);
}

void	internal_append_color(t_flexistr *fs, const char format, uint32_t color)
{
	const uint8_t	r = (color >> 16) & 0xFF;
	const uint8_t	g = (color >> 8) & 0xFF;
	const uint8_t	b = color & 0xFF;

	if (format && (format == 'F'))
	{
		fs_appendf(fs, "\033[38;2;%u;%u;%um", r, g, b);
	}
	else if (format && (format == 'B'))
	{
		fs_appendf(fs, "\033[48;2;%u;%u;%um", r, g, b);
	}
}
