/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/08 10:56:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/**
 * @def DEBUG
 * @brief Enables or disables debug mode.
 *
 * If set to 1, debug mode is enabled, allowing for additional debugging
 * information to be printed. By default, this is set to 0.
 */
# ifndef DEBUG
#  define DEBUG 0
# endif

# include "libft_allocation.h"
# include "libft_cleanup.h"
# include "libft_color.h"
# include "libft_comparison.h"
# include "libft_conversion.h"
# include "libft_count.h"
# include "libft_error.h"
# include "libft_flexistr.h"
# include "libft_flexistr_2d.h"
# include "libft_is.h"
# include "libft_list.h"
# include "libft_maths.h"
# include "libft_memory.h"
# include "libft_other.h"
# include "libft_print.h"
# include "libft_read.h"
# include "libft_skip.h"
# include "libft_sort.h"
# include "libft_string.h"

#endif
