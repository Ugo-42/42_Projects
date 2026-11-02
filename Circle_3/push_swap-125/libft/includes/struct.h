/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:51:56 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/21 13:37:59 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stddef.h>

/*┌──────────────┐
  │ Array Struct │
  └──────────────┘*/
typedef struct s_array
{
	void	*base;
	size_t	items_nb;
	size_t	type_size;
}	t_array;

/*┌──────────────┐
  │ Stack Struct │
  └──────────────┘*/
typedef struct s_stack
{
	void	*base;
	int		top;
	size_t	size;
	size_t	type_size;
}	t_stack;

typedef struct s_istack
{
	int		*base;
	int		top;
	size_t	size;
}	t_istack;

typedef struct s_cstack
{
	char	**base;
	int		top;
	size_t	size;
}	t_cstack;

#endif
