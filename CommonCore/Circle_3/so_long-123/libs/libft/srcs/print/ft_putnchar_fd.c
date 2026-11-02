/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/07 15:03:08 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnchar_fd(int fd, const char c, size_t n)
{
	char	*buffer;
	size_t	count;

	buffer = malloc(n);
	if (!buffer)
	{
		ft_exit_error(1, "In 'ft_putnspaces_fd': " BAD_ALLOC);
	}
	ft_memset(buffer, c, n);
	count = write(fd, buffer, n);
	free(buffer);
	return (count);
}
