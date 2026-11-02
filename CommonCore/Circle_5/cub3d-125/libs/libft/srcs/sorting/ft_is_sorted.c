/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:56:28 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_sorted(const void *base, size_t nmemb, size_t size,
			int (*cmp)(const void *, const void *))
{
	const unsigned char	*arr;
	size_t				i;

	if (!base || !cmp)
		ft_exit_error(1, "In 'ft_is_sorted': " BAD_ARG);
	arr = base;
	i = 0;
	while (i < nmemb - 1)
	{
		if (cmp(&arr[i * size], &arr[(i + 1) * size]) > 0)
			return (false);
		i++;
	}
	return (true);
}
