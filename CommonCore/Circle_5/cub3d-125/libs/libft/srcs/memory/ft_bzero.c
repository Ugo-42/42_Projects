/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/13 10:54:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	const size_t	word_size = sizeof(size_t);
	t_byte			*b;

	if (!s)
		ft_exit_error(1, "In 'ft_bzero': " BAD_ARG);
	b = (t_byte *)s;
	while (n >= word_size)
	{
		*(size_t *)b = 0;
		b += word_size;
		n -= word_size;
	}
	while (n--)
	{
		*b++ = 0;
	}
}
