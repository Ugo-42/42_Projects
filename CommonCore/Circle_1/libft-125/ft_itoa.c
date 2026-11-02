/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:35:14 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/28 10:57:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_total_len(int n)
{
	unsigned int	nb;
	int				len;

	len = 0;
	nb = n;
	if (n == 0)
		len++;
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
	int				len;
	int				i;

	len = ft_total_len(n);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	nb = n;
	if (n < 0)
		nb = -n;
	i = len;
	result[i--] = '\0';
	while (nb > 0)
	{
		result[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i--] = '-';
	return (result);
}
