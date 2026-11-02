/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
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

bool	ft_is_sorted(const void *base, size_t nmemb, size_t size,
			int (*cmp)(const void *, const void *));

void	ft_qsort(const void *base, size_t nmemb, size_t size,
			int (*cmp)(const void *, const void *));

#endif
