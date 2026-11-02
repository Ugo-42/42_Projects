/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:20 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/26 09:23:21 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_print.h"

size_t	ft_print_hex_fd(int fd, unsigned long n, bool uppercase)
{
	const char	*hex;
	char		result[17];
	int			i;

	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = 15;
	while (n > 0 || i == 15)
	{
		result[i--] = hex[n % 16];
		n /= 16;
	}
	result[16] = '\0';
	return (ft_putstr_fd(fd, &result[++i]));
}
