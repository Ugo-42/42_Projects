/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:50:59 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	if (!str)
		ft_exit_error(1, "In 'ft_atoi': " BAD_ARG);
	while ((*str >= 0x9 && *str <= 0x0D) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}
