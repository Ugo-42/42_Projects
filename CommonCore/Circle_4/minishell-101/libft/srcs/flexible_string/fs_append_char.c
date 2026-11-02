/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:27:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fs_append_char(t_flexistr *fs, const char c)
{
	if (!fs || !c)
	{
		if (fs)
			fs->errnum = 2;
		return (fs->last_append_len = 0, 1);
	}
	if (fs->len + 1 >= fs->size)
	{
		if (fs_resize(fs, ft_next_power_of_2(2 * (fs->len + 1))) != 0)
			return (fs->last_append_len = 0, fs->errnum = -1);
	}
	fs->string[fs->len++] = c;
	fs->string[fs->len] = '\0';
	fs->last_append_len = 1;
	return (fs->errnum = 0);
}
