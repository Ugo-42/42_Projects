/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:26:26 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_if(char *ptr, bool should_free)
{
	if (should_free)
	{
		free(ptr);
	}
}

int	fs_append(t_flexistr *fs, char *s, bool free_input)
{
	size_t	new_len;
	size_t	input_len;

	if (!fs || !s)
	{
		if (fs)
			fs->errnum = 2;
		free_if(s, free_input);
		return (fs->last_append_len = 0, 1);
	}
	input_len = ft_strlen(s);
	new_len = fs->len + input_len;
	if (new_len >= fs->size)
	{
		if (fs_resize(fs, ft_next_power_of_2(2 * new_len)) != 0)
		{
			free_if(s, free_input);
			return (fs->last_append_len = 0, fs->errnum = -1);
		}
	}
	ft_strcpy(fs->string + fs->len, s);
	fs->len = new_len;
	fs->last_append_len = input_len;
	free_if(s, free_input);
	return (fs->errnum = 0);
}
