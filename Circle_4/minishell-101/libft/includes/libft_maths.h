/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_maths.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:48:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/04 11:16:39 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATHS_H
# define LIBFT_MATHS_H

# include <stddef.h>

/*┌────────┐
  │ maths/ │
  └────────┘*/

/**
 * @brief Normalize number within `min` and `max` bounds.
 * @param nb The address of the number.
 * @param min The min value for number.
 * @param max The max value for number.
 */
void		ft_normalize(void *number, long min, long max);

/**
 * @brief Calculates the next power of 2 greater than the given number.
 *
 * Example: func(5) returns 8, func(8) returns 16.
 *
 * @param n The input number.
 * @return The next power of 2 greater than `n`.
 */
uint32_t	ft_next_power_of_2(uint32_t n);

/*┌──────────────────────┐
  │ String-based Numbers │
  └──────────────────────┘*/

/**
 * @brief Compares two string-based numbers.
 * @param nb1 The first string-based number.
 * @param nb2 The second string-based number.
 * @return A negative value if `nb1` is less than `nb2`, 0 if they are equal,
 *         or a positive value if `nb1` is greater than `nb2`.
 */
int			ft_cmp_strnb(const char *nb1, const char *nb2);

/**
 * @brief Finds the maximum value among an array of string-based numbers.
 * @param numbers An array of string-based numbers.
 * @return A pointer to the string representing the maximum value.
 */
char		*ft_max_strnb(char **numbers);

/**
 * @brief Finds the minimum value among an array of string-based numbers.
 * @param numbers An array of string-based numbers.
 * @return A pointer to the string representing the minimum value.
 */
char		*ft_min_strnb(char **numbers);

/**
 * @brief Calculates the percentile value from an array of string-based numbers.
 * @param numbers An array of string-based numbers.
 * @param nmemb The number of elements in the array.
 * @param percentile The desired percentile between 0 and 100%
 *                   (e.g., 50 for the median).
 * @return A pointer to the string representing the percentile value.
 */
char		*ft_percentile_strnb(char **numbers, size_t nmemb,
				double percentile);

#endif
