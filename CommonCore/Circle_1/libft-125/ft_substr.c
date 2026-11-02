/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:35:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/23 15:47:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	if (len > src_len - start)
		len = src_len - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strncpy(result, s + start, len);
	return (result);
}
