/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _benchmark.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:40:58 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/30 09:55:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#if BENCHMARK_ON

static inline void	print_result(t_benchmark *b, double avg_ms)
{
	if (b->flipflop)
	{
		printf(
			BG_DARK_RED LIGHT_BROWN "╭─┐╰─┐" LIGHT_RED " %-15s " LIGHT_BROWN
			"╰─┐│╭╯│╰╮│╭╮╰╯╭╯│╰─┐╭╮╰─┤│╭╯╰╮" RESET "\n" BG_DARKER_RED
			EMERAULD " min  =%7.3fms " BLACK "│"
			BLUE " avg  =%7.3fms " BLACK "│"
			ORANGE2 " max  =%7.3fms " RESET "\n",
			b->title, b->min_us / 1000.0, avg_ms, b->max_us / 1000.0 \
		);
	}
	else
	{
		printf(
			BG_DARK_PURPLE PURPLE "╭─┐╰─┐" LIGHT_PURPLE " %-15s " PURPLE
			"╰─┐│╭╯│╰╮│╭╮╰╯╭╯│╰─┐╭╮╰─┤│╭╯╰╮" RESET "\n" BG_DARKER_PURPLE
			TURQUOISE_GREEN " min  =%7.3fms " BLACK "│"
			SAPHIRE " avg  =%7.3fms " BLACK "│"
			ORANGE " max  =%7.3fms " RESET "\n",
			b->title, b->min_us / 1000.0, avg_ms, b->max_us / 1000.0 \
		);
	}
}

static long	get_duration_us(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000000L
		+ (end->tv_usec - start->tv_usec));
}

static double	ms_since(struct timeval *since)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - since->tv_sec) * 1000L
		+ (now.tv_usec - since->tv_usec) / 1000L);
}

void	_start_benchmark(t_benchmark *b, const char *title)
{
	gettimeofday(&b->start, NULL);
	if (!b->title)
	{
		b->title = title;
		b->min_us = __DBL_MAX__;
		gettimeofday(&b->last_print, NULL);
	}
}

void	_end_benchmark(t_benchmark *b)
{
	long	duration_us;
	double	avg_ms;

	gettimeofday(&b->end, NULL);
	duration_us = get_duration_us(&b->start, &b->end);
	if (duration_us < b->min_us)
		b->min_us = duration_us;
	if (duration_us > b->max_us)
		b->max_us = duration_us;
	b->total_us += duration_us;
	b->count++;
	if (ms_since(&b->last_print) >= BENCHMARK_UPDATE_MS)
	{
		avg_ms = 0.0;
		if (b->count > 0)
			avg_ms = (b->total_us / b->count) / 1000.0;
		b->flipflop = !b->flipflop;
		print_result(b, avg_ms);
		b->min_us = __DBL_MAX__;
		b->max_us = 0;
		b->total_us = 0;
		b->count = 0;
		gettimeofday(&b->last_print, NULL);
	}
}

#endif
