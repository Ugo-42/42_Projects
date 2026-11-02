/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_strnb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:54:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/30 15:31:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_is_negative(const char *nb)
{
	return (nb[0] == '-');
}

static int	ft_compare_negatives(const char *nb1, const char *nb2)
{
	size_t	len_nb1;
	size_t	len_nb2;

	len_nb1 = ft_strlen(nb1);
	len_nb2 = ft_strlen(nb2);
	if (len_nb1 > len_nb2)
		return (-1);
	if (len_nb1 < len_nb2)
		return (1);
	return (ft_strcmp(nb2 + 1, nb1 + 1));
}

static int	ft_compare_positives(const char *nb1, const char *nb2)
{
	size_t	len_nb1;
	size_t	len_nb2;

	len_nb1 = ft_strlen(nb1);
	len_nb2 = ft_strlen(nb2);
	if (len_nb1 > len_nb2)
		return (1);
	if (len_nb1 < len_nb2)
		return (-1);
	return (ft_strcmp(nb1, nb2));
}

int	ft_cmp_strnb(const char *nb1, const char *nb2)
{
	if (!nb1 || !nb2)
		ft_exit_error(1, "In 'ft_cmp_strnb': " BAD_ARG);
	if (ft_is_negative(nb1) && !ft_is_negative(nb2))
		return (-1);
	if (!ft_is_negative(nb1) && ft_is_negative(nb2))
		return (1);
	if (ft_is_negative(nb1) && ft_is_negative(nb2))
		return (ft_compare_negatives(nb1, nb2));
	else
		return (ft_compare_positives(nb1, nb2));
}
