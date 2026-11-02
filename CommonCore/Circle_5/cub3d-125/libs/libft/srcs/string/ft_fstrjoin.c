/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:53 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/26 09:30:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_input(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*ft_fstrjoin(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !*s1)
	{
		result = ft_strdup(s2);
		free_input(s1, s2);
		return (result);
	}
	if (!s2 || !*s2)
	{
		result = ft_strdup(s1);
		free_input(s1, s2);
		return (result);
	}
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
	free_input(s1, s2);
	return (result);
}
