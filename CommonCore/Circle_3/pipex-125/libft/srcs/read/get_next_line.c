/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:08:04 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/03 11:19:33 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_read.h"
#include "libft_allocation.h"

static int	read_and_copy(int fd, t_buffer *buf, char **line, size_t *line_len)
{
	if (buf->offset >= (size_t)buf->bytes_read)
	{
		buf->bytes_read = read(fd, buf->buffer, BUFFER_SIZE);
		buf->offset = 0;
		if (buf->bytes_read <= 0)
			return (buf->bytes_read);
	}
	(*line)[(*line_len)++] = buf->buffer[buf->offset++];
	return (1);
}

static char	*finalize_line(char *line, size_t line_len)
{
	if (line_len == 0)
	{
		free(line);
		return (NULL);
	}
	line[line_len] = '\0';
	return (line);
}

static char	*read_line(int fd, t_buffer *s_buffer)
{
	char	*line;
	size_t	alloc_size;
	size_t	line_len;

	alloc_size = 64;
	line = malloc(alloc_size);
	if (!line)
		return (NULL);
	line_len = 0;
	while (1)
	{
		if (line_len + 1 >= alloc_size)
		{
			line = ft_realloc(line, alloc_size, alloc_size * 2);
			if (!line)
				return (NULL);
			alloc_size *= 2;
		}
		if (read_and_copy(fd, s_buffer, &line, &line_len) <= 0)
			break ;
		if (line[line_len - 1] == '\n')
			break ;
	}
	return (finalize_line(line, line_len));
}

char	*get_next_line(int fd)
{
	static t_buffer	s_buffer[MAX_FD];

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	return (read_line(fd, &s_buffer[fd]));
}
