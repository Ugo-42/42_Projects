/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_instructions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:37:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/14 15:51:22 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_execute_instruction(t_cstack *a, t_cstack *b, char *instruction)
{
	if (!ft_strncmp(instruction, "sa\n", 3))
		ft_swap_a(a);
	else if (!ft_strncmp(instruction, "sb\n", 3))
		ft_swap_b(b);
	else if (!ft_strncmp(instruction, "ss\n", 3))
		ft_swap_ab(a, b);
	else if (!ft_strncmp(instruction, "pa\n", 3))
		ft_push_a(a, b);
	else if (!ft_strncmp(instruction, "pb\n", 3))
		ft_push_b(b, a);
	else if (!ft_strncmp(instruction, "ra\n", 3))
		ft_rotate_a(a);
	else if (!ft_strncmp(instruction, "rb\n", 3))
		ft_rotate_b(b);
	else if (!ft_strncmp(instruction, "rr\n", 3))
		ft_rotate_ab(a, b);
	else if (!ft_strncmp(instruction, "rra\n", 4))
		ft_reverse_rotate_a(a);
	else if (!ft_strncmp(instruction, "rrb\n", 4))
		ft_reverse_rotate_b(b);
	else if (!ft_strncmp(instruction, "rrr\n", 4))
		ft_reverse_rotate_ab(a, b);
}
