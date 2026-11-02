/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:20 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/20 10:17:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_a(t_cstack *a, t_instruction *instructions)
{
	size_t	i;
	char	*tmp;

	if (a->size > 1)
	{
		i = a->top + 1;
		tmp = a->base[a->top];
		while (i < (a->size + a->top))
		{
			a->base[i - 1] = a->base[i];
			i++;
		}
		a->base[i - 1] = tmp;
		ft_write_instruction(instructions, RA);
	}
}

void	ft_rotate_b(t_cstack *b, t_instruction *instructions)
{
	size_t	i;
	char	*tmp;

	if (b->size > 1)
	{
		i = b->top + 1;
		tmp = b->base[b->top];
		while (i < (b->size + b->top))
		{
			b->base[i - 1] = b->base[i];
			i++;
		}
		b->base[i - 1] = tmp;
		ft_write_instruction(instructions, RB);
	}
}

void	ft_rotate_ab(t_cstack *a, t_cstack *b, t_instruction *instructions)
{
	size_t	i;
	char	*tmp;

	if (a->size > 1 && b->size > 1)
	{
		i = a->top + 1;
		tmp = a->base[a->top];
		while (i < (a->size + a->top))
		{
			a->base[i - 1] = a->base[i];
			i++;
		}
		a->base[i - 1] = tmp;
		i = b->top + 1;
		tmp = b->base[b->top];
		while (i < (b->size + b->top))
		{
			b->base[i - 1] = b->base[i];
			i++;
		}
		b->base[i - 1] = tmp;
		ft_write_instruction(instructions, RR);
	}
}
