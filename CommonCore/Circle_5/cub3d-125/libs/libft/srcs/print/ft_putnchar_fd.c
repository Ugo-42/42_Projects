/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 15:58:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnchar_fd(int fd, const char c, size_t n)
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
