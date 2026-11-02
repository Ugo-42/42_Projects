/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_left_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:48:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 15:58:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_print_left_fd(int fd, const char *s, size_t padding)
{
	size_t	len;
	size_t	bytes;
	size_t	count;

	count = 0;
	if (s)
	{
		len = ft_utf8_visual_len(s);
		bytes = ft_strlen(s);
		if (padding > len)
			padding -= len;
		else
			padding = 0;
		count += write(fd, s, bytes);
	}
	count += ft_putnchar_fd(fd, ' ', padding);
	return (count);
}
