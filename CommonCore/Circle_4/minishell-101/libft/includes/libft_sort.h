/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/21 13:43:39 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SORT_H
# define LIBFT_SORT_H

/*┌──────────┐
  │ sorting/ │
  └──────────┘*/

# include "struct.h"
# include <stdbool.h>

/**
 * @brief Checks if an array is sorted.
 *
 * This function checks whether the elements in an array are sorted according
 * to a custom comparison function.
 *
 * @param base A pointer to the first element of the array.
 * @param nmemb The number of elements in the array.
 * @param size The size of each element in bytes.
 * @param cmp A pointer to the comparison function. (e.g., `ft_cmp_strnb`,
 *            `int_cmp`)
 * @return `true` if the array is sorted, otherwise `false`.
 */
bool	ft_is_sorted(const void *base, size_t nmemb, size_t size,
			int (*cmp)(const void *, const void *));

/**
 * @brief Sorts an array using the quicksort algorithm.
 *
 * This function sorts the elements in an array using the quicksort algorithm
 * and a custom comparison function.
 *
 * @param base A pointer to the first element of the array.
 * @param nmemb The number of elements in the array.
 * @param size The size of each element in bytes.
 * @param cmp A pointer to the comparison function. (e.g., `ft_cmp_strnb`,
 *            `int_cmp`)
 */
void	ft_qsort(const void *base, size_t nmemb, size_t size,
			int (*cmp)(const void *, const void *));

#endif
