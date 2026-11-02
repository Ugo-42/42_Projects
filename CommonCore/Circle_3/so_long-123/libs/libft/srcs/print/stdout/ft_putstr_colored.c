/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/27 10:07:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"

void	ft_putstr_colored(uint32_t color, const char *str)
{
	change_color(color);
	ft_putstr(str);
	reset_color();
}
