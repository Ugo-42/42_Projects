/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_stringf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:43:32 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/07/21 10:03:42 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*mm_stringf(const char *str, ...)
{
	va_list	args;
	char	*formatted;
	char	*result;

	va_start(args, str);
	formatted = ft_vstringf(str, args);
	result = mm_strdup(formatted);
	free(formatted);
	va_end(args);
	return (result);
}
