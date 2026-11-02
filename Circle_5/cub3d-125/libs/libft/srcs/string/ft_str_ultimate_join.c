/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ultimate_join.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:40:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:21 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_total_string_len(const char *first, va_list args)
{
	const char	*str;
	size_t		len;

	len = 0;
	str = first;
	while (str != NULL)
	{
		len += ft_strlen(str);
		str = va_arg(args, const char *);
	}
	return (len);
}

static void	ft_concatenate_strs(char *result, const char *first, va_list args)
{
	const char	*str;
	size_t		i;

	i = 0;
	str = first;
	while (str != NULL)
	{
		ft_strcpy(&result[i], str);
		i += ft_strlen(str);
		str = va_arg(args, const char *);
	}
}

char	*ft_str_ultimate_join(const char *first, ...)
{
	char	*result;
	va_list	args;

	if (!first)
		return (NULL);
	va_start(args, first);
	result = malloc((ft_total_string_len(first, args) + 1) * sizeof(char));
	va_end(args);
	if (!result)
		return (NULL);
	va_start(args, first);
	ft_concatenate_strs(result, first, args);
	va_end(args);
	return (result);
}
