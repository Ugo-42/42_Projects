/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_quoted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:55:14 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/05 14:56:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

#include "libft_skip.h"
#include "libft_is.h"

ssize_t	ft_count_words_quoted(const char *str)
{
	ssize_t		words;

	if (!str)
		return (0);
	words = 0;
	while (*str)
	{
		ft_skip_spaces(&str);
		if (!*str)
			break ;
		if (ft_isquote(*str))
		{
			if (ft_skip_quoted(&str) == -1)
				return (-1);
		}
		else
		{
			ft_skip_word(&str);
		}
		words++;
	}
	return (words);
}
