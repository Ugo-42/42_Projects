/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_other.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 09:40:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_OTHER_H
# define LIBFT_OTHER_H

/*┌────────┐
  │ other/ │
  └────────┘*/

# include <limits.h>
/**
 * @brief This function dereferences a NULL pointer.
 *
 * Known issue: This function can cause a segmentation fault if called.
 */
void			ft_segfault(void);

/**
 * @brief Exits the program once the function is called a specified
 *        number of times.
 *
 * @param max_calls The maximum number of allowed calls before exiting.
 */
void			ft_timeout(int max_calls);

/**
 * @brief Generate a random number between 0 and LONG_MAX
 */
unsigned long	ft_random(void);

#endif
