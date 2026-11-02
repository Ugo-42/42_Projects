/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:17:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 14:28:15 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	overflow(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (_strlen(argv[i++]) > 9)
			return (true);
	}
	if (argc == 6 && _strlen(argv[5]) > 9)
		return (true);
	return (false);
}

bool	parse_args(t_args *args, int argc, char **argv)
{
	if (overflow(argc, argv))
		return (!print_error("Invalid inputs (nb >= 1,000,000,000)."));
	args->philos_nb = _atoi(argv[1]);
	if (args->philos_nb > 666)
		return (!print_error("Invalid inputs (philos_nb >= 666)."));
	args->time2die = _atoi(argv[2]);
	args->time2eat = _atoi(argv[3]);
	args->time2sleep = _atoi(argv[4]);
	if (argc == 6)
	{
		args->max_meals = _atoi(argv[5]);
		if (args->max_meals < 0)
		{
			return (!print_error("Invalid inputs."));
		}
	}
	else
	{
		args->max_meals = -1;
	}
	if (args->philos_nb < 1 || args->time2die < 0 || args->time2eat < 0
		|| args->time2sleep < 0)
		return (!print_error("Invalid inputs."));
	return (true);
}
