/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:44:21 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/13 12:32:22 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_address(uintptr_t addr)
{
	if (!addr)
		return (write(1, "(nil)", 5));
	return (ft_putstrn("0x", 2) + ft_print_hex(addr, false));
}

size_t	ft_putstrn(const char *s, size_t n)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, n));
}

size_t	ft_putstr(const char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

size_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
