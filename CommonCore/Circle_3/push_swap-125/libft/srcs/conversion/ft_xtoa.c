/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:52:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_total_len(unsigned long n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_xtoa(unsigned long n, bool uppercase)
{
	const char	*hex;
	char		*result;
	size_t		len;
	size_t		i;

	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	len = ft_total_len(n);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = len;
	while (n > 0 || i == len)
	{
		result[--i] = hex[n % 16];
		n /= 16;
	}
	result[len] = '\0';
	return (result);
}
