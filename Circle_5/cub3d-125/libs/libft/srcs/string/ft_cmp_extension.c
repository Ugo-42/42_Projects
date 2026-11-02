/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_extension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:29:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/17 13:40:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_cmp_extension(const char *str, const char *ext)
{
	size_t	str_len;
	size_t	ext_len;

	if (!str || !ext)
		ft_exit_error(1, "In 'ft_strcmp_extension'" BAD_ARG);
	str_len = ft_strlen(str);
	ext_len = ft_strlen(ext);
	if (str_len < ext_len + 1)
		return (false);
	return (ft_strncmp(str + str_len - ext_len, ext, ext_len) == 0);
}
