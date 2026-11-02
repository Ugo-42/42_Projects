/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:48:58 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/25 15:29:52 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest++ = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
	return (result);
}
