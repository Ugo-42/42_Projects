/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:37:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/12 12:22:22 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_back(t_cstack *a, t_cstack *b, t_instruction *instructions)
{
	char	*max_nb;
	char	*to_push;
	size_t	index;

	while (b->size > 0)
	{
		max_nb = ft_max_strnb(&b->base[b->top]);
		if (!max_nb)
			return (ft_warning("In 'ft_push_back': " BAD_ARG));
		index = 0;
		while (cmp(b->base[b->top + index], max_nb) != 0)
			index++;
		to_push = b->base[b->top + index];
		if (index <= b->size / 2)
			while (b->base[b->top] != to_push)
				ft_rotate_b(b, instructions);
		else
			while (b->base[b->top] != to_push)
				ft_reverse_rotate_b(b, instructions);
		ft_push_a(a, b, instructions);
	}
}

void	ft_pre_sort(t_cstack *a, t_cstack *b, t_instruction *instructions,
			t_magic_value magic)
{
	size_t	index;
	char	*percentile;
	char	*to_push;

	percentile = ft_percentile_strnb(&a->base[a->top], a->size, magic.value1);
	index = 0;
	while (cmp(a->base[a->top + index], percentile) > 0)
		index++;
	to_push = a->base[a->top + index];
	if (index <= a->size / 2)
		while (a->base[a->top] != to_push)
			ft_rotate_a(a, instructions);
	else
		while (a->base[a->top] != to_push)
			ft_reverse_rotate_a(a, instructions);
	percentile = ft_percentile_strnb(&a->base[a->top], a->size, magic.value2);
	if (cmp(to_push, percentile) > 0)
	{
		ft_push_b(b, a, instructions);
		ft_rotate_b(b, instructions);
	}
	else
	{
		ft_push_b(b, a, instructions);
	}
}

void	ft_sort_three_moves(t_three_cmp res, t_cstack *a,
		t_instruction *instructions)
{
	if (res.cmp12 > 0 && res.cmp23 > 0)
	{
		ft_swap_a(a, instructions);
		ft_reverse_rotate_a(a, instructions);
	}
	else if (res.cmp12 < 0 && res.cmp23 > 0 && res.cmp13 < 0)
	{
		ft_swap_a(a, instructions);
		ft_rotate_a(a, instructions);
	}
	else if (res.cmp12 < 0 && res.cmp23 > 0 && res.cmp13 > 0)
	{
		ft_reverse_rotate_a(a, instructions);
	}
	else if (res.cmp12 > 0 && res.cmp23 < 0 && res.cmp13 > 0)
	{
		ft_rotate_a(a, instructions);
	}
	else if (res.cmp12 > 0 && res.cmp23 < 0 && res.cmp13 < 0)
	{
		ft_swap_a(a, instructions);
	}
}

void	ft_sort_three(t_cstack *a, t_instruction *instructions)
{
	t_three_nb	three;
	t_three_cmp	res;

	three = ft_init_three_nb(a);
	res = ft_init_three_cmp(three);
	ft_sort_three_moves(res, a, instructions);
}
