/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/20 10:16:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_a(t_cstack *a, t_cstack *b, t_instruction *instructions)
{
	if (b->size > 0)
	{
		a->base[a->top - 1] = b->base[b->top];
		a->top--;
		a->size++;
		b->base[b->top] = NULL;
		b->top++;
		b->size--;
		ft_write_instruction(instructions, PA);
	}
}

void	ft_push_b(t_cstack *b, t_cstack *a, t_instruction *instructions)
{
	if (a->size > 0)
	{
		b->base[b->top - 1] = a->base[a->top];
		b->top--;
		b->size++;
		a->base[a->top] = NULL;
		a->top++;
		a->size--;
		ft_write_instruction(instructions, PB);
	}
}
