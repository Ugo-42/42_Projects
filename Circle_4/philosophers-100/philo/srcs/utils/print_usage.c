/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:00:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/15 15:16:35 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define A GRAYISH_BLUE
#define B LIGHT_BLUE
#define C WHITE_BLUE
#define R RESET_COLOR

void	print_usage(void)
{
	printf(A
		"╭────────────────────────────────────────────────────────────╮\n"
		"│"B"                       PHILOSOPHERS                         "A"│\n"
		"├────────────────────────────────────────────────────────────┤\n"
		"│ Syntax:                                                    │\n"
		"│"C"   ./philosophers philosophers_nb time_to_die time_to_eat   "A"│\n"
		"│"C"         time_to_sleep [max_meals]                          "A"│\n"
		"├────────────────────────────────────────────────────────────┤\n"
		"│ Arguments:                                                 │\n"
		"│   philosophers_nb : "C"Number of philosophers (>=1)           "A"│\n"
		"│   time_to_die     : "C"Time (ms) before a philosopher dies    "A"│\n"
		"│   time_to_eat     : "C"Time (ms) for a philosopher to eat     "A"│\n"
		"│   time_to_sleep   : "C"Time (ms) for a philosopher to sleep   "A"│\n"
		"│   max_meals       : "C"Times each philosopher eats (Optional) "A"│\n"
		"╰────────────────────────────────────────────────────────────╯\n"R
		);
}
