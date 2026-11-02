/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_instruction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/10 15:03:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*ft_convert_instruction(enum e_instructions i)
{
	if (i == PA)
		return ("pa\n");
	if (i == PB)
		return ("pb\n");
	if (i == RA)
		return ("ra\n");
	if (i == RB)
		return ("rb\n");
	if (i == RR)
		return ("rr\n");
	if (i == RRA)
		return ("rra\n");
	if (i == RRB)
		return ("rrb\n");
	if (i == RRR)
		return ("rrr\n");
	if (i == SA)
		return ("sa\n");
	if (i == SB)
		return ("sb\n");
	if (i == SS)
		return ("ss\n");
	return (NULL);
}

void	ft_print_instruction(t_instruction *i)
{
	if (i->top < 0)
		return ;
	ft_putstr(ft_convert_instruction(i->stack[0]));
	if (i->top == 1)
	{
		i->stack[0] = i->stack[1];
	}
	i->top--;
}
