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

bool	ft_is_valid_instruction(const char *instruction)
{
	size_t				i;
	static const char	*valid_instructions[] = {
		"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n",
		"rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n", NULL
	};

	if (!instruction)
		return (false);
	i = 0;
	while (valid_instructions[i])
	{
		if (ft_strncmp(instruction, valid_instructions[i], 4) == 0)
			return (true);
		i++;
	}
	return (false);
}
