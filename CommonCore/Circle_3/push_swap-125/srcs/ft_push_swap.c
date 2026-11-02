/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                           	      +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/12 11:11:42 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_small_sort(t_cstack *a, t_instruction *instructions)
{
	if (a->size == 1)
		return ;
	if (a->size == 2 && ft_cmp_strnb(a->base[a->top], a->base[a->top + 1]) > 0)
		ft_swap_a(a, instructions);
	else
	{
		ft_sort_three(a, instructions);
	}
}

void	ft_push_swap(size_t nb_numbers, char **numbers)
{
	t_cstack		a;
	t_cstack		b;
	t_magic_value	magic;
	t_instruction	instructions;

	instructions.top = -1;
	if (ft_init_stacks(&a, &b, nb_numbers, numbers) == -1)
		ft_exit_error(3, "In 'ft_push_swap'" BAD_ALLOC);
	ft_init_magic(&magic, nb_numbers);
	if (a.size <= 3)
		ft_small_sort(&a, &instructions);
	else
	{
		while (a.size > 3)
			ft_pre_sort(&a, &b, &instructions, magic);
		ft_sort_three(&a, &instructions);
		ft_push_back(&a, &b, &instructions);
	}
	while (instructions.top >= 0)
		ft_print_instruction(&instructions);
	free(b.base);
}
