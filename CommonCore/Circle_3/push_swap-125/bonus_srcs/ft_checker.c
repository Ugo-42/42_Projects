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

#include "checker.h"
#include "color.h"

static void	ft_compute_instructions(t_cstack *a, t_cstack *b)
{
	char	*instruction;

	instruction = get_next_line(0);
	while (instruction)
	{
		if (!ft_is_valid_instruction(instruction))
		{
			ft_exit_error(1, "Invalid instruction.");
			free(instruction);
		}
		ft_execute_instruction(a, b, instruction);
		free(instruction);
		instruction = get_next_line(0);
	}
}

void	ft_checker(size_t nb_numbers, char **numbers)
{
	t_cstack	a;
	t_cstack	b;

	if (ft_init_stacks(&a, &b, nb_numbers, numbers) == -1)
		ft_exit_error(3, "In 'ft_push_swap'" BAD_ALLOC);
	ft_compute_instructions(&a, &b);
	if (!b.size && ft_is_sorted(a.base, a.size, sizeof(char *), ft_cmp_nb))
		ft_putstr(BOLD GREEN "OK\n" RESET_COLOR);
	else
		ft_putstr(BOLD RED "KO\n" RESET_COLOR);
	free(b.base);
}
