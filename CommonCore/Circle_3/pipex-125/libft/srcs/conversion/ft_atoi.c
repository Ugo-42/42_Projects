/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/26 09:21:49 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	if (!str)
		return (0);
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
	result *= sign;
	return (result);
}
