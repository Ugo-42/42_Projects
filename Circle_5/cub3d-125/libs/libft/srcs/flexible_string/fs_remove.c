/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:45:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:35:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fs_remove(t_flexistr *fs, size_t start, size_t end)
{
	size_t	new_len;
	size_t	remove_len;

	fs->last_remove_len = 0;
	if (!fs || !fs->string)
	{
		if (fs)
			fs->errnum = 2;
		return (1);
	}
	if (start >= fs->len || end < start)
		return (fs->errnum = 0);
	ft_normalize(&end, 0, fs->len - 1);
	ft_normalize(&start, 0, fs->len - 1);
	remove_len = end + 1 - start;
	ft_memmove(fs->string + start, fs->string + end + 1, fs->len - end);
	new_len = fs->len - remove_len;
	if (new_len < fs->size / 4)
	{
		if (fs_resize(fs, ft_next_power_of_2(2 * new_len)) != 0)
			return (fs->errnum = -1);
	}
	fs->len = new_len;
	fs->last_remove_len = remove_len;
	return (fs->errnum = 0);
}
