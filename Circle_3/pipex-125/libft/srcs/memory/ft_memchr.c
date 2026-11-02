/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:52 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/26 09:22:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*mem;
	unsigned char		byte;

	if (s)
	{
		byte = c;
		mem = s;
		while (n--)
		{
			if (*mem == byte)
				return ((void *)mem);
			mem++;
		}
	}
	return (NULL);
}
