/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:52:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(const char *str, const char c)
{
	size_t	words;

	if (!str)
		ft_exit_error(1, "In 'ft_count_words': " BAD_ARG);
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
