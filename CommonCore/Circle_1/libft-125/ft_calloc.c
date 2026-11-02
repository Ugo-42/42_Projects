/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:02:14 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/28 10:57:30 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*b;

	if (size && nmemb > ((size_t)-1) / size)
		return (NULL);
	b = malloc(nmemb * size);
	if (!b)
		return (NULL);
	ft_bzero(b, nmemb * size);
	return (b);
}
