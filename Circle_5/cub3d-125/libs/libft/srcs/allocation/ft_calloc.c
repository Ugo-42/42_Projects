/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:30 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:50:20 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*b;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	b = malloc(nmemb * size);
	if (!b)
		return (NULL);
	ft_bzero(b, nmemb * size);
	return (b);
}
