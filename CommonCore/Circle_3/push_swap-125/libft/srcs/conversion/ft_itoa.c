/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:51:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_total_len(int n)
{
	unsigned int	nb;
	size_t			len;

	len = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nb = -n;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*result;
	size_t			len;
	size_t			i;

	len = ft_total_len(n);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	nb = n;
	if (n < 0)
		nb = -n;
	i = len;
	while (nb > 0 || i == len)
	{
		result[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[--i] = '-';
	result[len] = '\0';
	return (result);
}
