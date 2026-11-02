/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:55:37 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_handle_alignment(va_list args, const char align, int fd)
{
	char	*str;
	size_t	padding;

	str = va_arg(args, char *);
	padding = va_arg(args, size_t);
	if (align == '<')
		return (ft_print_left_fd(fd, str, padding));
	if (align == '>')
		return (ft_print_right_fd(fd, str, padding));
	if (align == '^')
		return (ft_print_middle_fd(fd, str, padding));
	return (0);
}

static size_t	ft_handle_format(va_list args, const char *format, int fd)
{
	if (*format == '%')
		return (ft_putchar_fd(fd, '%'));
	else if (*format == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	else if (*format == 's')
		return (ft_putstr_fd(fd, va_arg(args, char *)));
	else if (*format == 'p')
		return (ft_print_address_fd(fd, va_arg(args, uintptr_t)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr_fd(fd, va_arg(args, int)));
	else if (*format == 'u')
		return (ft_putunbr_fd(fd, va_arg(args, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (ft_print_hex_fd(fd, va_arg(args, unsigned int),
				*format == 'X'));
	else if (*format == '<' || *format == '>' || *format == '^')
		return (ft_handle_alignment(args, *format, fd));
	else
		return (ft_putstrn_fd(fd, format - 1, 2));
}

int	ft_fprintf(int fd, const char *str, ...)
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
			count += ft_putstr_fd(fd, str);
			break ;
		}
		count += ft_putstrn_fd(fd, str, next_format - str);
		count += ft_handle_format(args, ++next_format, fd);
		if (*str == '%' && !*(str + 1))
			return (-1);
		str = next_format + 1;
	}
	va_end(args);
	return (count);
}
