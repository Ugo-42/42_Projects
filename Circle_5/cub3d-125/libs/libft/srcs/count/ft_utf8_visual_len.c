/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:53:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_utf8_visual_len(const char *s)
{
	size_t	i;
	size_t	len;

	if (!s)
		ft_exit_error(1, "In 'ft_utf8_visual_len': " BAD_ARG);
	len = 0;
	i = 0;
	while (s[i])
	{
		if (ft_is_emoji(&s[i]) || ft_is_cjk(&s[i]))
			len += 2;
		else
			len += 1;
		if ((s[i] & 0x80) == 0)
			i += 1;
		else if ((s[i] & 0xE0) == 0xC0)
			i += 2;
		else if ((s[i] & 0xF0) == 0xE0)
			i += 3;
		else if ((s[i] & 0xF8) == 0xF0)
			i += 4;
		else
			i++;
	}
	return (len);
}
