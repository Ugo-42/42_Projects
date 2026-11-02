/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:56:02 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstrn_fd(int fd, const char *s, size_t n)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, n));
}
