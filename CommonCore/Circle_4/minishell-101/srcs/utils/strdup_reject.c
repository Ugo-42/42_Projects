/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_reject.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:54:42 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/04 13:58:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strdup_reject(const char *src, const char *reject)
{
	char			*result;
	char			*tmp;
	const size_t	len = strlen(src);
	size_t			i;

	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (*src)
	{
		if (!ft_strchr(reject, *src))
			tmp[i++] = *src;
		src++;
	}
	tmp[i] = '\0';
	result = ft_strdup(tmp);
	return (free(tmp), result);
}
