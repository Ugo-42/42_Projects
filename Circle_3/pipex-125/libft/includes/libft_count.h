/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_count.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/05 15:24:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COUNT_H
# define LIBFT_COUNT_H

/* count/ */

# include <sys/types.h>

size_t	ft_count_words(const char *str, const char c);
size_t	ft_strlen(const char *str);
ssize_t	ft_count_words_quoted(const char *str);

#endif
