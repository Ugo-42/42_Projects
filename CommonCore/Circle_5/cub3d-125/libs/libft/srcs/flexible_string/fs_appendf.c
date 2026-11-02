/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_appendf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:28:58 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 10:51:09 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fs_appendf(t_flexistr *fs, const char *format, ...)
{
	va_list	args;
	char	*formatted;

	if (!fs || !format)
	{
		if (fs)
			fs->errnum = 2;
		return (fs->last_append_len = 0, 1);
	}
	va_start(args, format);
	formatted = ft_vstringf(format, args);
	va_end(args);
	if (!formatted)
		return (fs->last_append_len = 0, fs->errnum = -1);
	fs_append(fs, formatted, true);
	return (fs->errnum = 0);
}
