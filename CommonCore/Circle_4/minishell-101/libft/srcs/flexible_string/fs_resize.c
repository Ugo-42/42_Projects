/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_resize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:35:34 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fs_resize(t_flexistr *fs, size_t new_size)
{
	if (!fs || !new_size)
	{
		if (fs)
			fs->errnum = 2;
		return (1);
	}
	fs->string = ft_realloc(fs->string, fs->size, new_size);
	if (!fs->string)
	{
		fs_free(fs);
		return (fs->errnum = -1);
	}
	fs->size = new_size;
	if (new_size < fs->len)
	{
		fs->len = new_size - 1;
		fs->string[fs->len] = '\0';
	}
	return (fs->errnum = 0);
}
