/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:01:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/28 11:02:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	chr;

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
	return (NULL);
}
