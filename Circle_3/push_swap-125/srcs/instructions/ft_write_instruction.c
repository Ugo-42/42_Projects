/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_instruction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/20 10:16:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_write_instruction(t_instruction *i, enum e_instructions instruction)
{
	if (i->top == 1)
	{
		ft_combine(i);
	}
	i->stack[++i->top] = instruction;
}
