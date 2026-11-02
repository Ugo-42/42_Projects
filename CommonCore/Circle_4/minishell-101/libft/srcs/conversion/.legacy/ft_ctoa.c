/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:10:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:51:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ctoa(char c)
{
	char	*result;

	result = malloc(2 * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}
