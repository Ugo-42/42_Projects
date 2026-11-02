/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_count.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/07 14:30:09 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COUNT_H
# define LIBFT_COUNT_H

/*┌────────┐
  │ count/ │
  └────────┘*/

# include <sys/types.h>

size_t	ft_count_words(const char *str, const char c);
size_t	ft_strlen(const char *str);
size_t	ft_utf8_strlen(const char *str);
size_t	ft_utf8_charlen(const char *wide_c);
size_t	ft_utf8_visual_len(const char *str);
size_t	ft_utf8_count_bytes(const char *str, size_t n);
ssize_t	ft_count_words_quoted(const char *str);

#endif
