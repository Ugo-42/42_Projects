/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _disabled.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:35:37 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/28 19:39:19 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#if !BENCHMARK_ON

void	_start_benchmark(t_benchmark *b, const char *title)
{
	(void)b;
	(void)title;
}

void	_end_benchmark(t_benchmark *b)
{
	(void)b;
}

#endif
