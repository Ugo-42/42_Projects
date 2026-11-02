/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:35:14 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/28 11:02:29 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			result[12];
	int				i;

	if (n == 0)
	{
		ft_putstr_fd("0", fd);
		return ;
	}
	nb = n;
	if (n < 0)
		nb = -n;
	i = 11;
	result[i--] = '\0';
	while (nb > 0)
	{
		result[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i--] = '-';
	ft_putstr_fd(result + ++i, fd);
}
