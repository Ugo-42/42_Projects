/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_reset_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:11:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/05 14:26:49 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "internal/get_next_line.h"

void	gnl_reset_fd(int fd)
{
	t_buffer	*buffer;

	buffer = get_buffer(fd);
	if (!buffer)
		return ;
	buffer[fd].offset = 0;
	buffer[fd].bytes_read = 0;
}
