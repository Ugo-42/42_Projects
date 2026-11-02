/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_nl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/30 09:21:19 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_nl(const char *s)
{
	if (!s)
		return (write(1, "(null)\n", 7));
	return (write(1, s, ft_strlen(s)) + write(1, "\n", 1));
}
