/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_putnchar_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 15:59:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_utf8_putnchar_fd(int fd, const char *wide_c, size_t n)
{
	char	*buffer;
	size_t	count;
	size_t	len;
	size_t	i;

	if (!wide_c)
		ft_exit_error(1, "In 'ft_utf8_putnchar_fd': " BAD_ARG);
	if (n == 0)
		return (0);
	len = ft_utf8_charlen(wide_c);
	buffer = malloc(n * len);
	if (!buffer)
		ft_exit_error(1, "In 'ft_utf8_putnchar_fd': " BAD_ALLOC);
	i = 0;
	while (i < n)
	{
		ft_memcpy(buffer + (i * len), wide_c, len);
		i++;
	}
	count = write(fd, buffer, n * len);
	free(buffer);
	return (count);
}
