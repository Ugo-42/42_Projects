/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:59:16 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:56:46 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_malloc_word(char **result, size_t r, size_t word_len)
{
	result[r] = malloc((word_len + 1) * sizeof(char));
	if (!result[r])
	{
		while (r > 0)
			free(result[r--]);
		free(result[r]);
		free(result);
		return (0);
	}
	return (1);
}

static int	ft_split_words(char **result, const char *str, const char c)
{
	const char	*start;
	size_t		word_len;
	size_t		r;

	r = 0;
	while (*str)
	{
		ft_skip_chars(&str, c);
		if (!*str)
			break ;
		start = str;
		ft_skip_not_chars(&str, c);
		word_len = str - start;
		if (!ft_malloc_word(result, r, word_len))
			return (0);
		ft_strncpy(result[r++], start, word_len);
	}
	return (1);
}

char	**ft_split(const char *str, const char c)
{
	char	**result;
	int		words;

	if (!str)
		return (NULL);
	words = ft_count_words(str, c);
	if (!words)
		return (NULL);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!ft_split_words(result, str, c))
		return (NULL);
	result[words] = NULL;
	return (result);
}
