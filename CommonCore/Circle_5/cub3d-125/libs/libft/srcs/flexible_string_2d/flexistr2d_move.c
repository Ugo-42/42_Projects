/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexistr2d_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:52:57 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/09 09:23:34 by lrieffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flexistr2d_swap(t_flexistr2d *arstr, int src, int dest)
{
	if (!arstr)
		return ;
	ft_normalize(&src, 0, arstr->len);
	ft_normalize(&dest, 0, arstr->len);
	if (src == dest)
		return ;
	ft_swap_address(&arstr->str[src], &arstr->str[dest]);
}

static void	move_left(t_flexistr2d *arstr, int src, int dest)
{
	int	i;

	i = src;
	while (i < dest)
	{
		arstr->str[i] = arstr->str[i + 1];
		i++;
	}
}

static void	move_right(t_flexistr2d *arstr, int src, int dest)
{
	int	i;

	i = src;
	while (i > dest)
	{
		arstr->str[i] = arstr->str[i - 1];
		i--;
	}
}

void	flexistr2d_move(t_flexistr2d *arstr, int src, int dest)
{
	char	*temp;

	if (!arstr)
		return ;
	ft_normalize(&src, 0, arstr->len);
	ft_normalize(&dest, 0, arstr->len);
	if (src == dest)
		return ;
	temp = arstr->str[src];
	if (src < dest)
		move_left(arstr, src, dest);
	else
	{
		move_right(arstr, dest, src);
	}
	arstr->str[dest] = temp;
}
