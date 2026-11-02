/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/04 14:47:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_handle_alignment(va_list args, char type)
{
	char	*str;
	size_t	padding;

	str = va_arg(args, char *);
	padding = va_arg(args, size_t);
	if (type == '<')
		return (ft_print_left_fd(1, str, padding));
	if (type == '>')
		return (ft_print_right_fd(1, str, padding));
	if (type == '^')
		return (ft_print_middle_fd(1, str, padding));
	return (0);
}

static size_t	ft_handle_format(va_list args, const char *format)
{
	if (*format == '%')
		return (ft_putchar_fd(1, '%'));
	else if (*format == 'c')
		return (ft_putchar_fd(1, va_arg(args, int)));
	else if (*format == 's')
		return (ft_putstr_fd(1, va_arg(args, char *)));
	else if (*format == 'p')
		return (ft_print_address_fd(1, va_arg(args, uintptr_t)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr_fd(1, va_arg(args, int)));
	else if (*format == 'u')
		return (ft_putunbr_fd(1, va_arg(args, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (ft_print_hex_fd(1, va_arg(args, unsigned int), *format == 'X'));
	else if (*format == '<' || *format == '>' || *format == '^')
		return (ft_handle_alignment(args, *format));
	else
		return (ft_putstrn_fd(1, format - 1, 2));
}

int	ft_printf(const char *str, ...)
{
	const char	*next_format;
	va_list		args;
	size_t		count;

	if (!str || (str[0] == '%' && !str[1]))
		return (-1);
	va_start(args, str);
	count = 0;
	while (*str)
	{
		next_format = ft_strchr(str, '%');
		if (!next_format)
		{
			count += ft_putstr_fd(1, str);
			break ;
		}
		count += ft_putstrn_fd(1, str, next_format - str);
		count += ft_handle_format(args, ++next_format);
		if (*str == '%' && !*(str + 1))
			return (-1);
		str = next_format + 1;
	}
	va_end(args);
	return (count);
}
