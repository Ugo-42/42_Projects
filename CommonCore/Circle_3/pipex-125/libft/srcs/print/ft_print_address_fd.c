/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:15 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/26 09:23:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_print.h"

size_t	ft_print_address_fd(int fd, uintptr_t addr)
{
	if (!addr)
		return (write(fd, "(nil)", 5));
	return (ft_putstrn_fd(fd, "0x", 2) + ft_print_hex_fd(fd, addr, false));
}
