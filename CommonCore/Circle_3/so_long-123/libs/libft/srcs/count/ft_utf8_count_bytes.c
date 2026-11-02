/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_count_bytes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:00:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/08 12:00:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_utf8_count_bytes(const char *str, size_t n)
{
	size_t	byte_count;
	size_t	char_count;

	if (!str)
		ft_exit_error(1, "In 'ft_utf8_count_bytes': " BAD_ARG);
	char_count = 0;
	byte_count = 0;
	while (str[byte_count] && char_count < n)
	{
		if ((str[byte_count] & 0x80) == 0)
			byte_count += 1;
		else if ((str[byte_count] & 0xE0) == 0xC0)
			byte_count += 2;
		else if ((str[byte_count] & 0xF0) == 0xE0)
			byte_count += 3;
		else if ((str[byte_count] & 0xF8) == 0xF0)
			byte_count += 4;
		else
			byte_count++;
		char_count++;
	}
	return (byte_count);
}
