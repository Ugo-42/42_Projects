/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:38:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/12 11:13:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_STRUCT_H
# define PS_STRUCT_H

# include "struct.h"

enum e_instructions
{
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	SA,
	SB,
	SS
};

typedef struct s_percentile
{
	char	*first_quartile;
	char	*median;
	char	*third_quartile;
	char	*min;
	char	*max;
}	t_percentile;

typedef struct s_instructions
{
	enum e_instructions	stack[2];
	int					top;
}	t_instruction;

typedef struct s_three_nb
{
	char	*first_nb;
	char	*second_nb;
	char	*third_nb;
}	t_three_nb;

typedef struct s_three_cmp
{
	int	cmp12;
	int	cmp23;
	int	cmp13;
}	t_three_cmp;

typedef struct s_magic_value
{
	double	value1;
	double	value2;
}	t_magic_value;

#endif
