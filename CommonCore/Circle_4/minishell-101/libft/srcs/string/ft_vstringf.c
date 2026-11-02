/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vstringf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 11:42:23 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "internal/ft_vstringf.h"

static void	handle_format_extended(t_flexistr *fs, va_list args,
	const char format)
{
	long	b_nb;

	if (format == 'b')
	{
		b_nb = va_arg(args, long);
		fs_append_nb(fs, b_nb, va_arg(args, char *));
	}
	if (format == 'R')
		fs_append(fs, "\033[0m", false);
	if (format == 'F')
		internal_append_color(fs, format, va_arg(args, uint32_t));
	if (format == 'B')
		internal_append_color(fs, format, va_arg(args, uint32_t));
}

static void	handle_format(t_flexistr *fs, va_list args, const char format)
{
	if (format == '%')
		fs_append_char(fs, '%');
	else if (format == 'c')
		fs_append_char(fs, va_arg(args, int));
	else if (format == 's')
		internal_append_str(fs, va_arg(args, char *));
	else if (format == 'p')
		internal_append_ptr(fs, va_arg(args, uintptr_t));
	else if (format == 'i' || format == 'd')
		fs_append_nb(fs, va_arg(args, int), NULL);
	else if (format == 'l')
		fs_append_nb(fs, va_arg(args, long), NULL);
	else if (format == 'u')
		fs_append_nb(fs, va_arg(args, unsigned int), NULL);
	else if (format == 'x')
		fs_append_nb(fs, va_arg(args, unsigned long), "0123456789abcdef");
	else if (format == 'X')
		fs_append_nb(fs, va_arg(args, unsigned long), "0123456789ABCDEF");
	else
		handle_format_extended(fs, args, format);
}

static void	handle_alignment(t_flexistr *fs, va_list args, const char *str)
{
	size_t	padding;
	size_t	pad_len;

	padding = va_arg(args, size_t);
	handle_format(fs, args, *(str + 1));
	if (fs->last_append_len >= padding)
		return ;
	pad_len = padding - fs->last_append_len;
	if (*str == '<')
		internal_pad(fs, pad_len, fs->len);
	else if (*str == '>')
		internal_pad(fs, pad_len, fs->len - fs->last_append_len);
	else if (*str == '^')
	{
		internal_pad_middle(fs, pad_len, fs->len - fs->last_append_len);
	}
}

char	*ft_vstringf(const char *str, va_list args)
{
	t_flexistr	fs;
	size_t		len;

	if (!str || fs_init(&fs, 256) != 0)
		return (NULL);
	while (*str)
	{
		len = ft_strcspn(str, "%");
		fs_n_append(&fs, str, len);
		str += len;
		if (!*str || !*(str + 1))
			break ;
		if (*(str + 1) == '<' || *(str + 1) == '>' || *(str + 1) == '^')
			handle_alignment(&fs, args, ++str);
		else
			handle_format(&fs, args, *(str + 1));
		if (!fs.string)
			return (NULL);
		str += 2;
	}
	return (fs_finalize(&fs));
}
