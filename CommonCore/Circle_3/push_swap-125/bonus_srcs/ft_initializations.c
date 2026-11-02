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

#include "checker.h"

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
