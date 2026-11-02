/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid_stack.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:21:47 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/17 09:56:13 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "color.h"

void	ft_int_limited(char **numbers)
{
	size_t	nb;

	nb = 0;
	while (numbers[nb])
	{
		if (ft_cmp_strnb(numbers[nb], "2147483647") > 0)
			ft_fexit_error(3, ft_stringf("Too high number: '%s'", numbers[nb]));
		if (ft_cmp_strnb(numbers[nb], "-2147483648") < 0)
			ft_fexit_error(3, ft_stringf("Too low number: '%s'", numbers[nb]));
		nb++;
	}
}

static int	ft_skip_leading_sign_x_zeros(char **numbers, size_t nb, size_t i)
{
	i = 0;
	if (numbers[nb][i] == '+' || numbers[nb][i] == '-')
		i++;
	while (numbers[nb][i] == '0' && numbers[nb][i + 1] != '\0')
		i++;
	return (i);
}

static void	ft_check_valid_numbers(char **numbers)
{
	size_t	i;
	size_t	nb;
	size_t	start;

	nb = 0;
	while (numbers[nb])
	{
		if (!numbers[nb][0])
			ft_exit_error(1, "Empty string in arguments.");
		i = ft_skip_leading_sign_x_zeros(numbers, nb, i);
		start = i;
		while (numbers[nb][i] >= '0' && numbers[nb][i] <= '9')
			i++;
		if (numbers[nb][i] != '\0')
			ft_fexit_error(1, ft_stringf("Invalid number format: '%s' "
					"(base 10 number only)", numbers[nb]));
		if (numbers[nb][0] == '-' && numbers[nb][start] != '0')
		{
			numbers[nb][start - 1] = '-';
			numbers[nb] += start - 1;
		}
		else
			numbers[nb] += start;
		nb++;
	}
}

static void	ft_check_dupped_number(char **numbers)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (numbers[i])
	{
		j = i + 1;
		while (numbers[j])
		{
			if (ft_strcmp(numbers[i], numbers[j]) == 0)
				ft_fexit_error(2, ft_stringf("Number %s is duplicated",
						numbers[i]));
			j++;
		}
		i++;
	}
}

void	ft_check_valid_stack(char **numbers)
{
	ft_check_valid_numbers(numbers);
	ft_check_dupped_number(numbers);
}
