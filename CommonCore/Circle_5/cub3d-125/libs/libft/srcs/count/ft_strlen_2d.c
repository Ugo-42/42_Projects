/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/31 16:57:34 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_2d(char **array)
{
	size_t	count;

	if (!array)
		ft_exit_error(1, "In 'ft_strlen_2d': " BAD_ARG);
	count = 0;
	while (array[count])
		count++;
	return (count);
}
