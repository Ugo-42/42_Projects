/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:04:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/11 11:55:21 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap_char_address(char **a, char **b)
{
	ft_swap_address((void **)a, (void **)b);
}

int	ft_cmp_nb(const void *a, const void *b)
{
	return (ft_cmp_strnb(*(const char **)a, *(const char **)b));
}

int	cmp(const char *a, const char *b)
{
	return (ft_cmp_strnb(a, b));
}
