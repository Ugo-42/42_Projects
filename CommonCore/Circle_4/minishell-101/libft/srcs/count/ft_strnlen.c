/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/01 11:50:22 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *str, size_t max_len)
{
	size_t	i;

	if (!str)
		ft_exit_error(1, "In 'ft_strnlen': " BAD_ARG);
	i = 0;
	while (str[i] && i < max_len)
		i++;
	return (i);
}
