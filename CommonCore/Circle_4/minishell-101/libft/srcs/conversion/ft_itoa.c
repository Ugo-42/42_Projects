/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:51:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			result[12];
	unsigned int	nb;
	size_t			i;

	nb = ft_iternary((n < 0), -n, n);
	result[11] = '\0';
	i = 10;
	while (nb > 0 || i == 10)
	{
		result[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i--] = '-';
	return (ft_strdup(&result[i + 1]));
}
