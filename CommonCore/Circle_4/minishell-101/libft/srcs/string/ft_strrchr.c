/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	chr;
	int				i;

	if (s)
	{
		str = (unsigned char *)s;
		chr = c;
		i = ft_strlen(s);
		if (!chr)
			return ((char *)str + i);
		while (i--)
			if (str[i] == chr)
				return ((char *)str + i);
	}
	return (NULL);
}
