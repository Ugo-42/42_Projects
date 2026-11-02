/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:58 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_utf8_visual_strncpy(char *dest, const char *src, size_t n)
{
	size_t	char_len;
	size_t	next_width;
	size_t	visual_width;

	if (!dest || !src)
		ft_exit_error(1, "In 'ft_utf8_visual_strncpy': " BAD_ARG);
	visual_width = 0;
	while (*src)
	{
		char_len = ft_utf8_charlen(src);
		next_width = 1;
		if (ft_is_emoji(src) || ft_is_cjk(src))
			next_width = 2;
		if (visual_width + next_width > n)
			break ;
		visual_width += next_width;
		ft_memcpy(dest, src, char_len);
		dest += char_len;
		src += char_len;
	}
	*dest = '\0';
}
