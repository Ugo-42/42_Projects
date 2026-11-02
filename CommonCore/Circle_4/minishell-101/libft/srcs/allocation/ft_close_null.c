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

/* Takes the ADDRESS to a file descriptor, frees it, and puts it to -1 */

int	ft_close_null(int *fd)
{
	int	err_num;

	if (*fd != -1)
	{
		err_num = close(*fd);
		*fd = -1;
		return (err_num);
	}
	return (-1);
}
