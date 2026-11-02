/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:08:19 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 11:39:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_pad_str(size_t size)
{
	char	*ptr;

	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, ' ', size);
	ptr[size] = '\0';
	return (ptr);
}

void	internal_pad(t_flexistr *fs, size_t pad_len, size_t index)
{
	char	*pad_str;

	pad_str = create_pad_str(pad_len);
	if (!pad_str)
		return ;
	fs_add(fs, pad_str, index);
	free(pad_str);
}

void	internal_pad_middle(t_flexistr *fs, size_t pad_len, size_t left_index)
{
	char	*lpad_str;
	char	*rpad_str;
	size_t	left_pad;
	size_t	right_pad;

	left_pad = pad_len / 2;
	right_pad = pad_len - left_pad;
	lpad_str = create_pad_str(left_pad);
	rpad_str = create_pad_str(right_pad);
	if (!lpad_str || !rpad_str)
	{
		free(lpad_str);
		free(rpad_str);
		return ;
	}
	fs_add(fs, lpad_str, left_index);
	fs_add(fs, rpad_str, fs->len);
	free(lpad_str);
	free(rpad_str);
}
