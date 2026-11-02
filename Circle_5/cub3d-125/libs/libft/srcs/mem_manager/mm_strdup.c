/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/13 14:49:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*mm_strdup(const char *s)
{
	char	*start;
	char	*copy;

	if (!s)
		return (NULL);
	copy = mm_alloc((ft_strlen(s) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	start = copy;
	while (*s)
		*copy++ = *s++;
	*copy = '\0';
	return (start);
}
