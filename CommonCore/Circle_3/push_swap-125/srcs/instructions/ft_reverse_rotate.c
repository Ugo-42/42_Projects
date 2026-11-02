/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate_instructions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/20 10:16:35 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_reverse_rotate_a(t_cstack *a, t_instruction *instructions)
{
	char	*tmp;
	int		i;

	if (a->size > 1)
	{
		i = a->size + a->top - 1;
		tmp = a->base[a->size + a->top - 1];
		while (i > a->top)
		{
			a->base[i] = a->base[i - 1];
			i--;
		}
		a->base[a->top] = tmp;
		ft_write_instruction(instructions, RRA);
	}
}

void	ft_reverse_rotate_b(t_cstack *b, t_instruction *instructions)
{
	char	*tmp;
	int		i;

	if (b->size > 1)
	{
		i = b->size + b->top - 1;
		tmp = b->base[b->size + b->top - 1];
		while (i > b->top)
		{
			b->base[i] = b->base[i - 1];
			i--;
		}
		b->base[b->top] = tmp;
		ft_write_instruction(instructions, RRB);
	}
}

void	ft_reverse_rotate_ab(t_cstack *a, t_cstack *b, t_instruction *instructs)
{
	char	*tmp;
	int		i;

	if (a->size > 1 && b->size > 1)
	{
		i = a->size + a->top - 1;
		tmp = a->base[a->size + a->top - 1];
		while (i > a->top)
		{
			a->base[i] = a->base[i - 1];
			i--;
		}
		a->base[a->top] = tmp;
		i = b->size + b->top - 1;
		tmp = b->base[b->size + b->top - 1];
		while (i > b->top)
		{
			b->base[i] = b->base[i - 1];
			i--;
		}
		b->base[b->top] = tmp;
		ft_write_instruction(instructs, RRR);
	}
}
