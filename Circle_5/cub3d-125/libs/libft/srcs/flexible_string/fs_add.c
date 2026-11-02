/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:10:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 12:10:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fs_add(t_flexistr *fs, const char *s, size_t index)
{
	size_t	input_len;
	size_t	new_len;

	fs->last_append_len = 0;
	if (!fs || !fs->string || !s)
	{
		if (fs)
			fs->errnum = 2;
		return (1);
	}
	ft_normalize(&index, 0, fs->len);
	input_len = ft_strlen(s);
	new_len = fs->len + input_len;
	if (new_len >= fs->size)
	{
		if (fs_resize(fs, ft_next_power_of_2(2 * new_len)) != 0)
			return (fs->errnum = -1);
	}
	ft_memmove(fs->string + index + input_len, fs->string + index,
		fs->len - index + 1);
	ft_memcpy(fs->string + index, s, input_len);
	fs->len = new_len;
	fs->last_append_len = input_len;
	return (fs->errnum = 0);
}
