/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_strnb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:24:37 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:54:33 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_min_strnb(char **numbers)
{
	char	*min_nb;
	size_t	nb;

	if (!numbers)
		ft_exit_error(1, "In 'ft_min_strnb': " BAD_ARG);
	nb = 0;
	min_nb = numbers[nb];
	while (numbers[nb])
	{
		if (ft_cmp_strnb(numbers[nb], min_nb) < 0)
			min_nb = numbers[nb];
		nb++;
	}
	return (min_nb);
}
