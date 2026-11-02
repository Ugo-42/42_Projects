/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_middle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:48:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/04 15:51:43 by ugwentzi         ###   ########.fr       */
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
	size_t	left_pad;

	len = ft_utf8_visual_len(s);
	bytes = ft_strlen(s);
	if (padding > len)
		padding -= len;
	else
		padding = 0;
	left_pad = padding / 2;
	total_len = bytes + left_pad + (padding - left_pad);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	ft_memset(result, ' ', left_pad);
	ft_memcpy(result + left_pad, s, bytes);
	ft_memset(result + left_pad + bytes, ' ', (padding - left_pad));
	result[total_len] = '\0';
	return (result);
}

char	*ft_str_middle_padded(const char *s, size_t padding)
{
	if (!s)
		return (ft_handle_null_string(padding));
	return (ft_create_padded_string(s, padding));
}
