/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:44:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/13 12:33:37 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr(int n)
{
	unsigned int	nb;
	char			result[12];
	int				i;

	nb = n;
	if (n < 0)
		nb = -n;
	i = 11;
	result[i--] = '\0';
	while (nb > 0 || i == 10)
	{
		result[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i--] = '-';
	return (ft_putstr(&result[++i]));
}

size_t	ft_putunbr(unsigned int n)
{
	char	result[11];
	int		i;

	i = 10;
	result[i--] = '\0';
	while (n > 0 || i == 9)
	{
		result[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (ft_putstr(&result[++i]));
}

size_t	ft_print_hex(unsigned long n, bool uppercase)
{
	const char	*hex;
	char		result[17];
	int			i;

	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = 16;
	result[i--] = '\0';
	while (n > 0 || i == 15)
	{
		result[i--] = hex[n % 16];
		n /= 16;
	}
	return (ft_putstr(&result[++i]));
}
