/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 15:59:01 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putunbr_fd(int fd, unsigned int n)
{
	char	result[11];
	int		i;

	i = 9;
	while (n > 0 || i == 9)
	{
		result[i--] = (n % 10) + '0';
		n /= 10;
	}
	result[10] = '\0';
	return (ft_putstr_fd(fd, &result[++i]));
}
