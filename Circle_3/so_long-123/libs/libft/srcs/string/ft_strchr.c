/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:56:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	chr;

	if (s)
	{
		str = (unsigned char *)s;
		chr = c;
		while (*str)
		{
			if (*str == chr)
				return ((char *)str);
			str++;
		}
		if (!chr)
			return ((char *)str);
	}
	return (NULL);
}
