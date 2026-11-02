/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:38:30 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/04 12:43:54 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define MAX_BUFFER_SIZE 10000000

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# if BUFFER_SIZE > MAX_BUFFER_SIZE
#  undef BUFFER_SIZE
#  define BUFFER_SIZE MAX_BUFFER_SIZE
# endif

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	*ft_memmove(void *dest, const void *src, size_t n);

char	*ft_strncpy(char *dest, size_t start, const char *src, size_t n);
char	*get_next_line(int fd);

ssize_t	ft_is_eol(char *str, ssize_t n);

#endif
