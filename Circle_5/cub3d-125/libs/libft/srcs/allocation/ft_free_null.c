/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:22:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/03 09:32:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes the ADDRESS of a pointer, frees it, and puts it to NULL */

void	*ft_free_null(void *pointer_address)
{
	void	**pointer;

	if (!pointer_address)
		return (NULL);
	pointer = (void **)pointer_address;
	if (*pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
	return (NULL);
}
