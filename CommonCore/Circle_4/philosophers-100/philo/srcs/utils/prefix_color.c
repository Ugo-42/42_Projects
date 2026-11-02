/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:53:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 11:43:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifdef COLOR_ON

# define UNIFORM_MASK 0xA5A5A5A5A5A5A5A5ULL
# define GOLDEN_RATIO 0x9E3779B97F4A7C15ULL

# define MULT1 0xBF58476D1CE4E5B9ULL
# define MULT2 0x94D049BB133111EBULL

unsigned long	ft_random(unsigned long seed)
{
	unsigned long	z;

	seed += GOLDEN_RATIO;
	z = seed;
	z = (z ^ (z >> 30)) * MULT1;
	z = (z ^ (z >> 27)) * MULT2;
	z = z ^ (z >> 31);
	return (z & 0xFFFFFF);
}

int	ternary(int cond, int ret_true, int ret_false)
{
	if (cond)
		return (ret_true);
	return (ret_false);
}

void	normalize(int *r, int *g, int *b)
{
	int	sum;
	int	adjust;

	sum = *r + *g + *b;
	if (sum < 255)
	{
		adjust = (255 - sum) / 3;
		*r += adjust;
		*g += adjust;
		*b += adjust;
		*r = ternary((*r > 255), 255, *r);
		*g = ternary((*g > 255), 255, *g);
		*b = ternary((*b > 255), 255, *b);
	}
	else if (sum > 512)
	{
		*r = ternary((*r > 200), *r - 75, *r);
		*g = ternary((*g > 200), *g - 75, *g);
		*b = ternary((*b > 200), *b - 75, *b);
	}
}

void	color_prefix(int id)
{
	const unsigned long	color = ft_random(id);
	int					r;
	int					g;
	int					b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	normalize(&r, &g, &b);
	printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

#else

void	color_prefix(int id)
{
	(void)id;
}

#endif
