/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializations.c                               :+:      :+:    :+:   */
/*                                           	      +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/12 12:16:23 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_init_stacks(t_cstack *a, t_cstack *b, size_t nb_numbers, char **numbers)
{
	b->base = calloc(nb_numbers + 1, sizeof(char *));
	if (!b->base)
		return (-1);
	b->size = 0;
	b->top = nb_numbers;
	a->base = numbers;
	a->size = nb_numbers;
	a->top = 0;
	return (0);
}

void	ft_init_magic(t_magic_value *magic, size_t nb_numbers)
{
	if (nb_numbers <= 200)
	{
		magic->value1 = 20;
		magic->value2 = 5;
	}
	else if (nb_numbers <= 500)
	{
		magic->value1 = 12.5;
		magic->value2 = 3.75;
	}
	else if (nb_numbers <= 1000)
	{
		magic->value1 = 8.8;
		magic->value2 = 2.5;
	}
	else
	{
		magic->value1 = 7.7;
		magic->value2 = 2.2;
	}
}

void	ft_init_percentiles(t_percentile *p, t_cstack *a)
{
	p->first_quartile = ft_percentile_strnb(a->base + a->top, a->size, 25);
	p->median = ft_percentile_strnb(a->base + a->top, a->size, 50);
	p->third_quartile = ft_percentile_strnb(a->base + a->top, a->size, 75);
	p->min = ft_min_strnb(a->base + a->top);
	p->max = ft_max_strnb(a->base + a->top);
}

t_three_nb	ft_init_three_nb(t_cstack *a)
{
	t_three_nb	three;

	three.first_nb = a->base[a->top];
	three.second_nb = a->base[a->top + 1];
	three.third_nb = a->base[a->top + 2];
	return (three);
}

t_three_cmp	ft_init_three_cmp(t_three_nb three)
{
	t_three_cmp	res;

	res.cmp12 = cmp(three.first_nb, three.second_nb);
	res.cmp23 = cmp(three.second_nb, three.third_nb);
	res.cmp13 = cmp(three.first_nb, three.third_nb);
	return (res);
}
