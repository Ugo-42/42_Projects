/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:52:53 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/12 15:35:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	size_t	nb_numbers;
	char	**numbers;

	if (argc <= 1)
		return (0);
	nb_numbers = argc - 1;
	numbers = argv + 1;
	ft_check_valid_stack(numbers);
	if (INT_LIMITED)
		ft_int_limited(numbers);
	if (nb_numbers < 2)
		return (0);
	if (ft_is_sorted(numbers, nb_numbers, sizeof(char *), ft_cmp_nb))
		return (0);
	ft_push_swap(nb_numbers, numbers);
	return (0);
}
