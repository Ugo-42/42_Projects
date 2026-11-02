/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_handle_alignment(va_list args, char type)
{
	char	*str;
	size_t	padding;

	str = va_arg(args, char *);
	padding = va_arg(args, size_t);
	if (type == '<')
		return (ft_str_left_padded(str, padding));
	if (type == '>')
		return (ft_str_right_padded(str, padding));
	if (type == '^')
		return (ft_str_middle_padded(str, padding));
	return (0);
}

static char	*ft_handle_format(va_list args, const char *format)
{
	if (*format == '%')
		return (ft_strdup("%"));
	else if (*format == 'c')
		return (ft_ctoa(va_arg(args, int)));
	else if (*format == 's')
		return (ft_strdup(va_arg(args, char *)));
	else if (*format == 'p' || *format == 'P')
		return (ft_addrtoa(va_arg(args, uintptr_t), *format == 'P'));
	else if (*format == 'd' || *format == 'i')
		return (ft_itoa(va_arg(args, int)));
	else if (*format == 'u')
		return (ft_utoa(va_arg(args, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (ft_xtoa(va_arg(args, unsigned int), *format == 'X'));
	else if (*format == '<' || *format == '>' || *format == '^')
		return (ft_handle_alignment(args, *format));
	else
		return (NULL);
}

static void	ft_append(char **dest, const char *src, size_t len)
{
	char	*result;
	size_t	old_len;

	if (src)
	{
		old_len = 0;
		if (*dest)
			old_len = ft_strlen(*dest);
		result = ft_realloc(*dest, old_len, old_len + len + 1);
		if (!result)
			return ;
		ft_memcpy(result + old_len, src, len);
		result[old_len + len] = '\0';
		*dest = result;
	}
}

static int	ft_format_the_string(const char **str, char **result, va_list args)
{
	const char	*next_format;
	char		*tmp;

	next_format = ft_strchr(*str, '%');
	if (!next_format)
	{
		ft_append(result, *str, ft_strlen(*str));
		return (0);
	}
	ft_append(result, *str, next_format - *str);
	tmp = ft_handle_format(args, ++next_format);
	ft_append(result, tmp, ft_strlen(tmp));
	free(tmp);
	if ((*str)[0] == '%' && !(*str)[1])
		return (-1);
	*str = next_format + 1;
	return (1);
}

char	*ft_stringf(const char *str, ...)
{
	char	*result;
	va_list	args;

	if (!str || (str[0] == '%' && !str[1]))
		return (NULL);
	va_start(args, str);
	result = NULL;
	while (*str)
	{
		if (ft_format_the_string(&str, &result, args) <= 0)
			break ;
	}
	va_end(args);
	return (result);
}
