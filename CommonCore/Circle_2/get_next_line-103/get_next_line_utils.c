/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:36:29 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/04 10:15:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = dest;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = (unsigned char *)dest + n;
	s = (const unsigned char *)src + n;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
		while (n--)
			*--d = *--s;
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*result;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	result = malloc(new_size);
	if (!result)
		return (NULL);
	if (old_size < new_size)
		new_size = old_size;
	ft_memcpy(result, ptr, new_size);
	free(ptr);
	return (result);
}

char	*ft_strncpy(char *dest, size_t start, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[start + i] = src[i];
		i++;
	}
	dest[start + i] = '\0';
	return (dest);
}

ssize_t	ft_is_eol(char *str, ssize_t n)
{
	ssize_t	i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
