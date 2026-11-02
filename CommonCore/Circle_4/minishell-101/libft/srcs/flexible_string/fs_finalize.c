/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_finalize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:28:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fs_finalize(t_flexistr *fs)
{
	char	*result;

	if (!fs)
		return (NULL);
	result = ft_strndup(fs->string, fs->len);
	if (!result)
		return (fs->errnum = -1, NULL);
	fs_free(fs);
	return (fs->errnum = 0, result);
}
