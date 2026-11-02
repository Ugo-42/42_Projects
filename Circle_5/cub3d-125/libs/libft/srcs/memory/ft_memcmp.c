/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:55:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*b1;
	unsigned const char	*b2;
	size_t				i;

	if (!s1 || !s2 || n == 0)
		return (0);
	b1 = s1;
	b2 = s2;
	i = 0;
	while (i < n - 1 && b1[i] == b2[i])
		i++;
	return (b1[i] - b2[i]);
}
