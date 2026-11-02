/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:06 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/13 10:52:57 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	const size_t	word = (t_byte)c * (SIZE_MAX / 0xFF);
	const size_t	word_size = sizeof(size_t);
	t_byte			*b;

	if (!s)
		ft_exit_error(1, "In 'ft_memset': " BAD_ARG);
	b = (t_byte *)s;
	while (n >= word_size)
	{
		*(size_t *)b = word;
		b += word_size;
		n -= word_size;
	}
	while (n--)
	{
		*b++ = (t_byte)c;
	}
	return (s);
}
