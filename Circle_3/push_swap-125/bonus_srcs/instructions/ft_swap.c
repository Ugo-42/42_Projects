/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:12:12 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/06 11:40:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_swap_a(t_cstack *a)
{
	if (a->size >= 2)
	{
		ft_swap_char_address(&a->base[a->top], &a->base[a->top + 1]);
	}
}

void	ft_swap_b(t_cstack *b)
{
	if (b->size >= 2)
	{
		ft_swap_char_address(&b->base[b->top], &b->base[b->top + 1]);
	}
}

void	ft_swap_ab(t_cstack *a, t_cstack *b)
{
	ft_swap_a(a);
	ft_swap_b(b);
}
