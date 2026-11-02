/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/13 12:32:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_handle_format(va_list args, const char *format)
{
	if (*format == '%')
		return (ft_putchar('%'));
	else if (*format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (*format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (*format == 'p')
		return (ft_print_address(va_arg(args, uintptr_t)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (*format == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), *format == 'X'));
	else
		return (ft_putstrn(format - 1, 2));
}

int	ft_printf(const char *str, ...)
{
	const char	*next_format;
	va_list		args;
	size_t		count;

	if (!str || (*str == '%' && !*(str + 1)))
		return (-1);
	count = 0;
	va_start(args, str);
	while (*str)
	{
		next_format = ft_strchr(str, '%');
		if (!next_format)
		{
			count += ft_putstr(str);
			break ;
		}
		ft_putstrn(str, next_format - str);
		count += next_format - str;
		count += ft_handle_format(args, ++next_format);
		if (!*next_format)
			return (-1);
		str = next_format + 1;
	}
	va_end(args);
	return (count);
}
