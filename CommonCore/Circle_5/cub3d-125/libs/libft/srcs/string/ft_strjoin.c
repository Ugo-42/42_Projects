/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:53 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/25 15:53:23 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (!s1 || !*s1)
		return (ft_strdup(s2));
	if (!s2 || !*s2)
		return (ft_strdup(s1));
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
	return (result);
}
