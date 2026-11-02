/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_maths.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:48:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/21 13:41:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATHS_H
# define LIBFT_MATHS_H

# include <stddef.h>

/*┌────────┐
  │ maths/ │
  └────────┘*/

/* String Numbers */

int		ft_cmp_strnb(const char *nb1, const char *nb2);

char	*ft_max_strnb(char **numbers);
char	*ft_min_strnb(char **numbers);

char	*ft_percentile_strnb(char **numbers, size_t nmemb, double percentile);

#endif
