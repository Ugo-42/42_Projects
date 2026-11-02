/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/23 09:56:38 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
'*  Algorithm:
'*  {
'*      1. We allocate a stack to store the start and end indices of subarrays.
'*      2. The stack is initialized with the entire array as indices.
'*      3. While (the stack is not empty)
'*      {
'*          a. Pop the current subarray boundaries
'*          b. Partition the subarray around a pivot element,
'*             rearranging elements such that:
'*               - All elements <= to the pivot are on the left.
'*               - All elements > than the pivot are on the right.
'*          c. If the right subarray (pivot + 1 to end) > than one element
'*                 push its boundaries onto the stack.
'*          d. If the left subarray (start to pivot - 1) > than one element
'*                 push its boundaries onto the stack.
'*      }
'*      4. when the stack is empty, all subarrays have been sorted.
'*  }
*/

#include "libft.h"
#include "struct.h"

static int	partition(t_array *arr, int left, int right,
		int (*cmp)(const void *, const void *))
{
	void	*pivot;
	char	*base;
	int		i;
	int		j;

	base = arr->base;
	pivot = base + right * arr->type_size;
	i = left - 1;
	j = left;
	while (j < right)
	{
		if (cmp(base + j * arr->type_size, pivot) <= 0)
		{
			i++;
			ft_swap_content(base + i * arr->type_size,
				base + j * arr->type_size, arr->type_size);
		}
		j++;
	}
	ft_swap_content(base + (i + 1) * arr->type_size,
		base + right * arr->type_size, arr->type_size);
	return (i + 1);
}

static void	ft_push_stack(t_istack *stack, int start, int end)
{
	size_t	total_size;

	if (stack->top + 2 >= (int)stack->size)
	{
		total_size = stack->size * sizeof(int *);
		stack->base = ft_realloc(stack->base, total_size, total_size * 2);
		if (!stack->base)
		{
			ft_exit_error(1, "In 'ft_qsort': " BAD_ALLOC);
		}
		stack->size *= 2;
	}
	stack->base[++stack->top] = start;
	stack->base[++stack->top] = end;
}

static void	ft_pop_stack(t_istack *stack, int *start, int *end)
{
	*end = stack->base[stack->top--];
	*start = stack->base[stack->top--];
}

static void	ft_init_stack(t_istack *stack)
{
	stack->size = 64;
	stack->base = malloc(stack->size * sizeof(int *));
	if (!stack->base)
	{
		ft_exit_error(1, "In 'ft_qsort': " BAD_ALLOC);
	}
}

void	ft_qsort(const void *base, size_t nmemb, size_t size,
			int (*cmp)(const void *, const void *))
{
	t_istack	stack;
	t_array		arr;
	int			start;
	int			end;
	int			pivot;

	if (!base || !cmp)
		ft_exit_error(1, "In 'ft_qsort': " BAD_ARG);
	arr.base = (void *)base;
	arr.items_nb = nmemb;
	arr.type_size = size;
	ft_init_stack(&stack);
	stack.top = -1;
	ft_push_stack(&stack, 0, arr.items_nb - 1);
	while (stack.top >= 0)
	{
		ft_pop_stack(&stack, &start, &end);
		pivot = partition(&arr, start, end, cmp);
		if (pivot + 1 < end)
			ft_push_stack(&stack, pivot + 1, end);
		if (start < pivot - 1)
			ft_push_stack(&stack, start, pivot - 1);
	}
	free(stack.base);
}
