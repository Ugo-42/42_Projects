/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:24:01 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (big && little)
	{
		if (*little == '\0')
			return ((char *)big);
		i = 0;
		while (big[i] && i < len)
		{
			j = i;
			k = 0;
			while (big[j] == little[k] && j < len)
			{
				if (little[++k] == '\0')
					return ((char *)&big[i]);
				j++;
			}
			i++;
		}
	}
	return (NULL);
}
