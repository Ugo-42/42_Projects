/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:01:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/28 10:59:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*mem;
	unsigned char		byte;

	byte = c;
	mem = s;
	while (n--)
	{
		if (*mem == byte)
			return ((void *)mem);
		mem++;
	}
	return (NULL);
}
