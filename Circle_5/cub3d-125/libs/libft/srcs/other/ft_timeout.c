/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timeout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/29 16:54:54 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"

void	ft_timeout(int max_calls)
{
	static int	timeout;

	if (timeout++ == max_calls)
	{
		ft_putstr(BOLD TOP_LOW_LINE RED "Timeout\n" RESET_COLOR);
		exit(0);
	}
}
