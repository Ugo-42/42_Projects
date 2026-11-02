/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/04 14:47:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*formatted;
	int		count;

	va_start(args, format);
	formatted = ft_vstringf(format, args);
	va_end(args);
	if (!formatted)
		return (-1);
	count = write(1, formatted, ft_strlen(formatted));
	free(formatted);
	return (count);
}
