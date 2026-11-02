/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:58 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_utf8_strncpy(char *dest, const char *src, size_t n)
{
	size_t	copied_chars;
	size_t	char_len;

	if (!dest || !src)
		ft_exit_error(1, "In 'ft_utf8_strncpy': " BAD_ARG);
	copied_chars = 0;
	while (*src && copied_chars < n)
	{
		char_len = ft_utf8_charlen(src);
		if (copied_chars + 1 <= n)
		{
			ft_memcpy(dest, src, char_len);
			dest += char_len;
			src += char_len;
			copied_chars++;
		}
	}
	*dest = '\0';
}
