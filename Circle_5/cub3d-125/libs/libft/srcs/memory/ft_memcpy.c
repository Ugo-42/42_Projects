/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:55:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_byte			*d;
	t_byte const	*s;
	const size_t	word_size = sizeof(size_t);

	if (!dest && !src)
		ft_exit_error(1, "In 'ft_memcpy': " BAD_ARG);
	d = (t_byte *)dest;
	s = (t_byte const *)src;
	while (n >= word_size)
	{
		*(size_t *)d = *(const size_t *)s;
		d += word_size;
		s += word_size;
		n -= word_size;
	}
	while (n--)
		*d++ = *s++;
	return (dest);
}
