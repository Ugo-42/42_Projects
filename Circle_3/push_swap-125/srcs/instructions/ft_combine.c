/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_combine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/11 11:15:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	ft_is_pair(t_instruction *i,
	enum e_instructions a, enum e_instructions b)
{
	return ((i->stack[0] == a && i->stack[1] == b)
		|| (i->stack[0] == b && i->stack[1] == a));
}

void	ft_combine(t_instruction *i)
{
	if (i->top < 1)
		return ;
	if (ft_is_pair(i, RA, RB))
	{
		i->stack[0] = RR;
		i->top--;
	}
	else if (ft_is_pair(i, RRA, RRB))
	{
		i->stack[0] = RRR;
		i->top--;
	}
	else if (ft_is_pair(i, SA, SB))
	{
		i->stack[0] = SS;
		i->top--;
	}
	else if (ft_is_pair(i, PA, PB) || ft_is_pair(i, RRA, RA)
		|| ft_is_pair(i, RRB, RB))
	{
		i->top -= 2;
	}
	ft_print_instruction(i);
}
