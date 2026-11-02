/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/08 12:00:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_utf8_strlen(const char *str)
{
	size_t	len;
	size_t	i;

	if (!str)
		ft_exit_error(1, "In 'ft_utf8_strlen': " BAD_ARG);
	len = 0;
	i = 0;
	while (str[i])
	{
		len++;
		if ((str[i] & 0xF0) == 0xF0)
			i += 4;
		else if ((str[i] & 0xE0) == 0xE0)
			i += 3;
		else if ((str[i] & 0xC0) == 0xC0)
			i += 2;
		else
			i++;
	}
	return (len);
}
