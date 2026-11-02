/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_middle_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:48:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/04 15:51:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_print_middle_fd(int fd, const char *s, size_t padding)
{
	size_t	len;
	size_t	bytes;
	size_t	count;
	size_t	left_pad;
	size_t	right_pad;

	count = 0;
	if (s)
	{
		len = ft_utf8_visual_len(s);
		bytes = ft_strlen(s);
		if (padding > len)
			padding -= len;
		else
			padding = 0;
		left_pad = padding / 2;
		right_pad = padding - left_pad;
		count += ft_putnchar_fd(fd, ' ', left_pad);
		count += ft_putstrn_fd(fd, s, bytes);
		count += ft_putnchar_fd(fd, ' ', right_pad);
	}
	else
		count += ft_putnchar_fd(fd, ' ', padding);
	return (count);
}
