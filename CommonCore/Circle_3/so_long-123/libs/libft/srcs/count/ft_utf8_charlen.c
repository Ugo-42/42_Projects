/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_charlen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/07 15:22:47 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_utf8_charlen(const char *wide_c)
{
	unsigned char	byte;

	if (!wide_c)
		ft_exit_error(1, "In 'ft_utf8_charlen': " BAD_ARG);
	byte = (unsigned char)wide_c[0];
	if ((byte & 0x80) == 0)
		return (1);
	if ((byte & 0xE0) == 0xC0)
		return (2);
	if ((byte & 0xF0) == 0xE0)
		return (3);
	if ((byte & 0xF8) == 0xF0)
		return (4);
	return (1);
}
