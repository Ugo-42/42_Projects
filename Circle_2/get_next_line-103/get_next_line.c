/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/04 16:05:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_handle_buffer(char *buffer, ssize_t *count, char **r, size_t *s)
{
	ssize_t			eol;
	ssize_t			i;

	eol = ft_is_eol(buffer, BUFFER_SIZE);
	if (eol >= 0)
	{
		*count = ft_strlen(buffer) - eol - 1;
		ft_memmove(buffer, buffer + eol + 1, *count);
		i = 0;
		while (*count + i < BUFFER_SIZE)
			buffer[*count + i++] = '\0';
	}
	else
	{
		i = 0;
		while (i < BUFFER_SIZE)
			buffer[i++] = '\0';
		*count = 0;
	}
	*r = NULL;
	*s = 0;
	return (buffer);
}

static void	ft_fill_buffer(int fd, char *buffer, ssize_t *count, ssize_t eol)
{
	size_t	i;

	if (!*buffer || eol < 0)
	{
		*count = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		if (*count > 0)
		{
			while (*count + i != BUFFER_SIZE)
				buffer[*count + i++] = '\0';
		}
	}
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*result;
	ssize_t			count;
	size_t			size;
	ssize_t			eol;

	ft_handle_buffer(buffer, &count, &result, &size);
	while (true)
	{
		result = ft_realloc(result, size + 1, size + BUFFER_SIZE + 1);
		if (!result)
			return (NULL);
		ft_fill_buffer(fd, buffer, &count, eol);
		if (count == -1 || (count == 0 && !*buffer))
			return (free(result), NULL);
		if (count == 0 && *buffer)
			return (result);
		eol = ft_is_eol(buffer, count);
		if (eol >= 0)
			return (ft_strncpy(result, size, buffer, count),
				result[size + eol + 1] = '\0', result);
		ft_strncpy(result, size, buffer, count);
		size += count;
	}
	return (result);
}
