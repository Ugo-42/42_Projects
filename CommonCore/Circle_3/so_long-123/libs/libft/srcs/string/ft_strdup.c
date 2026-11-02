/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:57:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*start;
	char	*copy;

	if (!s)
		return (NULL);
	copy = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	start = copy;
	while (*s)
		*copy++ = *s++;
	*copy = '\0';
	return (start);
}
