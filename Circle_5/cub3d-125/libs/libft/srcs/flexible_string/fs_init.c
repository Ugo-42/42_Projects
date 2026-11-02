/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:31:41 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fs_init(t_flexistr *fs, size_t initial_size)
{
	if (!fs || !initial_size)
	{
		if (fs)
			fs->errnum = 2;
		return (1);
	}
	fs->len = 0;
	fs->last_append_len = 0;
	fs->last_remove_len = 0;
	fs->string = malloc(initial_size);
	if (!fs->string)
	{
		fs->size = 0;
		return (fs->errnum = -1);
	}
	fs->size = initial_size;
	fs->string[0] = '\0';
	return (fs->errnum = 0);
}
