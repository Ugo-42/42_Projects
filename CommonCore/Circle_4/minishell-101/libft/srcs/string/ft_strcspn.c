/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:55 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/25 10:59:34 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;

	if (!s || !reject)
		return (0);
	i = 0;
	while (s[i] && ft_is_not_in_set(s[i], reject))
		i++;
	return (i);
}
