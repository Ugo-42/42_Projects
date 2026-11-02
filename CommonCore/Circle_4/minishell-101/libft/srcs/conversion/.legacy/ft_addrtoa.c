/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addrtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:21:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:50:54 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_addrtoa(uintptr_t addr, bool uppercase)
{
	char	*result;
	char	*tmp;

	tmp = ft_xtoa(addr, uppercase);
	if (!tmp)
		return (NULL);
	result = ft_strjoin("0x", tmp);
	free(tmp);
	return (result);
}
