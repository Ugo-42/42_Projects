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

/**
 * @struct s_array
 * @brief Represents a generic array.
 *
 * @param base Pointer to the base of the array.
 * @param items_nb The number of items in the array.
 * @param type_size The size of each item in the array (in bytes).
 */
typedef struct s_array
{
	void	*base;
	size_t	items_nb;
	size_t	type_size;
}	t_array;

/*┌──────────────┐
  │ Stack Struct │
  └──────────────┘*/

/**
 * @struct s_stack
 * @brief Represents a generic stack.
 *
 * @param base Pointer to the base of the stack.
 * @param top The index of the top element in the stack.
 * @param size The total size of the stack.
 * @param type_size The size of each element in the stack (in bytes).
 */
typedef struct s_stack
{
	void	*base;
	int		top;
	size_t	size;
	size_t	type_size;
}	t_stack;

/**
 * @struct s_istack
 * @brief Represents a stack of integers.
 *
 * @param base Pointer to the base of the integer stack.
 * @param top The index of the top element in the stack.
 * @param size The total size of the stack.
 */
typedef struct s_istack
{
	int		*base;
	int		top;
	size_t	size;
}	t_istack;

/**
 * @struct s_cstack
 * @brief Represents a stack of strings (character pointers).
 *
 * @param base Pointer to the base of the string stack.
 * @param top The index of the top element in the stack.
 * @param size The total size of the stack.
 */
typedef struct s_cstack
{
	char	**base;
	int		top;
	size_t	size;
}	t_cstack;

/*┌──────────────┐
  │ Color Struct │
  └──────────────┘*/

/**
 * @struct s_rgb
 * @brief Represents an RGB color.
 *
 * @param r The red component of the color (0-255).
 * @param g The green component of the color (0-255).
 * @param b The blue component of the color (0-255).
 */
typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

#endif
