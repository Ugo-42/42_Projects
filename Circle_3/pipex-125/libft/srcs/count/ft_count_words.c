/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/05 15:27:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft_skip.h"

size_t	ft_count_words(const char *str, const char c)
{
	size_t	words;

	if (!str)
		return (0);
	words = 0;
	while (*str)
	{
		ft_skip_chars(&str, c);
		if (!*str)
			break ;
		ft_skip_not_chars(&str, c);
		words++;
	}
	return (words);
}
