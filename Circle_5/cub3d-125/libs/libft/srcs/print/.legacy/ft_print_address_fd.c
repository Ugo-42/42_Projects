/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:15 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 15:58:18 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_print_address_fd(int fd, uintptr_t addr)
{
	if (!addr)
		return (write(fd, "(nil)", 5));
	return (ft_putstrn_fd(fd, "0x", 2) + ft_print_hex_fd(fd, addr, false));
}
