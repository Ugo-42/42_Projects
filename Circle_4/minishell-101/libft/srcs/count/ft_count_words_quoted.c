/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_quoted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:55:14 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:52:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_count_words_quoted(const char *str)
{
	ssize_t		words;

	if (!str)
	{
		ft_exit_error(1, "In 'ft_count_words_quoted': " BAD_ARG);
	}
	words = 0;
	while (*str)
	{
		ft_skip_spaces(&str);
		if (!*str)
			break ;
		while (*str && !ft_is_space(*str))
		{
			if (ft_is_quote(*str))
			{
				if (ft_skip_quoted(&str) == -1)
					return (-1);
			}
			else
				str++;
		}
		words++;
	}
	return (words);
}
