/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/14 15:08:19 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_rainbow(const char *str)
{
	while (*str)
	{
		ft_loop_color();
		ft_putchar(*str++);
	}
	ft_reset_color();
}
