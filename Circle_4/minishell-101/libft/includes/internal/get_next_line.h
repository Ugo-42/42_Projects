/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:23:55 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/05 14:27:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*┌─────────────────┐
  │ get_next_line.c │
  └─────────────────┘*/

# define BUFFER_SIZE 4096
# define MAX_FD 1024

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE];
	size_t	offset;
	ssize_t	bytes_read;
}	t_buffer;

t_buffer	*get_buffer(int fd);

#endif
