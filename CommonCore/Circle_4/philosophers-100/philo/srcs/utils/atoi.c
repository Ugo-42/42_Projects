/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/16 10:09:50 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	_atoi(const char *str)
{
	int	sign;
	int	result;

	if (!str)
		return (-1);
	while ((*str >= 0x9 && *str <= 0x0D) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (-1);
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	if (*str && (*str < '0' || *str > '9'))
		return (-1);
	return (result * sign);
}
