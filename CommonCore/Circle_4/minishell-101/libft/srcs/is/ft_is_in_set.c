/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:34:55 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/20 09:44:21 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_in_set(const char c, const char *set)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}
