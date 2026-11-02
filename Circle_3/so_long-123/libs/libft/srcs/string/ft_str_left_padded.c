/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_handle_null_string(size_t padding)
{
	char	*result;

	result = malloc(padding + 1);
	if (!result)
		return (NULL);
	ft_memset(result, ' ', padding);
	result[padding] = '\0';
	return (result);
}

static char	*ft_create_padded_string(const char *s, size_t padding)
{
	size_t	len;
	size_t	bytes;
	size_t	total_len;
	char	*result;

	len = ft_utf8_visual_len(s);
	bytes = ft_strlen(s);
	if (padding > len)
		padding -= len;
	else
		padding = 0;
	total_len = bytes + padding;
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s, bytes);
	ft_memset(result + bytes, ' ', padding);
	result[total_len] = '\0';
	return (result);
}

char	*ft_str_left_padded(const char *s, size_t padding)
{
	if (!s)
		return (ft_handle_null_string(padding));
	return (ft_create_padded_string(s, padding));
}
