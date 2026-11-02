/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:53:26 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/08 13:33:17 by lrieffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*flexistr2d_close(t_flexistr2d *arstr)
{
	arstr->len = 0;
	arstr->alloc_size = 0;
	ft_free_2d_char_array(&arstr->str);
	*arstr = (t_flexistr2d){0};
	return (NULL);
}
