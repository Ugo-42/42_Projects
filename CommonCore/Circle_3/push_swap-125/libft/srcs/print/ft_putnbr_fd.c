/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:55:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int fd, int n)
{
	unsigned int	nb;
	char			result[12];
	int				i;

	nb = n;
	if (n < 0)
		nb = -n;
	i = 10;
	while (nb > 0 || i == 10)
	{
		result[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i--] = '-';
	result[11] = '\0';
	return (ft_putstr_fd(fd, &result[++i]));
}
