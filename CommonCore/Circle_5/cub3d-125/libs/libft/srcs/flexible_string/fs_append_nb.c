/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_append_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 11:27:50 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_valid_char(const char c, bool is_base10)
{
	return ((c > 32 && c < 127) && (!is_base10 || c != '-'));
}

const char	*check_base(const char *base, int *radix)
{
	const char	*fallback_base = "0123456789";
	size_t		base_len;
	int			i;

	*radix = 10;
	if (!base)
		return (fallback_base);
	base_len = ft_strlen(base);
	i = 0;
	while (base[i])
	{
		if (!is_valid_char(base[i], base_len == 10))
			return (fallback_base);
		if (base[i + 1] && ft_strchr(&base[i + 1], base[i]) != NULL)
			return (fallback_base);
		i++;
	}
	if (i < 2)
		return (fallback_base);
	*radix = i;
	return (base);
}

static int	convert_and_append(t_flexistr *fs, long nb, const char *base,
		int radix)
{
	char			buffer[65];
	int				i;
	unsigned long	n;

	buffer[64] = '\0';
	n = ft_iternary(nb < 0, -nb, nb);
	i = 63;
	while (n > 0 || i == 63)
	{
		buffer[i--] = base[n % radix];
		n /= radix;
	}
	if (nb < 0 && radix == 10)
		buffer[i--] = '-';
	return (fs_append(fs, &buffer[i + 1], false));
}

int	fs_append_nb(t_flexistr *fs, long nb, const char *base)
{
	int			radix;
	const char	*valid_base = check_base(base, &radix);

	if (!fs)
		return (1);
	return (convert_and_append(fs, nb, valid_base, radix));
}
