/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:08:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:55:29 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX_SIZE 256

void	ft_swap_content(void *a, void *b, size_t type_size)
{
	unsigned char	tmp[MAX_SIZE];

	if (type_size > MAX_SIZE)
	{
		ft_exit_error(1, "In 'ft_swap_content': object size to big.");
	}
	if (!a || !b)
	{
		ft_exit_error(1, "In 'ft_swap_content': " BAD_ARG);
	}
	ft_memcpy(tmp, a, type_size);
	ft_memcpy(a, b, type_size);
	ft_memcpy(b, tmp, type_size);
}
