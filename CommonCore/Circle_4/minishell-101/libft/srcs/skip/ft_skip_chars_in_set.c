/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_chars_in_set.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:27:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/20 09:45:47 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_chars_in_set(const char **str, const char *set)
{
	while (**str && ft_is_in_set(**str, set))
		(*str)++;
}
