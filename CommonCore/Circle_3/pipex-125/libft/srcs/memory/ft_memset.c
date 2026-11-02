/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:06 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/26 09:23:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*b;

	if (!s)
		return (NULL);
	b = s;
	while (n--)
		*b++ = c;
	return (s);
}
