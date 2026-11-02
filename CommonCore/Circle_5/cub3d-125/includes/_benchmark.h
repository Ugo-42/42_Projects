/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _benchmark.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:54:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/28 14:58:30 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BENCHMARK_H
# define _BENCHMARK_H

# include "cub3d.h"

# if BENCHMARK_ON

int		printf(const char *format, ...);

#  ifndef __DBL_MAX__
#   define __DBL_MAX__ 1.7976931348623157E+308
#  endif

#  define BENCHMARK_UPDATE_MS 666

typedef struct s_benchmark
{
	struct timeval	start;
	struct timeval	end;
	struct timeval	last_print;
	const char		*title;
	double			min_us;
	double			max_us;
	double			total_us;
	int				count;
	bool			flipflop;
}	t_benchmark;

# else

typedef struct s_benchmark
{
}	t_benchmark;

# endif

void	_start_benchmark(t_benchmark *b, const char *title);
void	_end_benchmark(t_benchmark *b);

#endif
