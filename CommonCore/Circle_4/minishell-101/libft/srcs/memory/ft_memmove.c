/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:55:18 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_revmemcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = dest + n;
	s = src + n;
	while (n--)
		*--d = *--s;
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return (NULL);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
		ft_revmemcpy(dest, src, n);
	return (dest);
}
