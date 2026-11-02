/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:05:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/10/25 15:38:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(const char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static int	ft_trim_len(const char *s, const char *set, int src_len,
	const char **end)
{
	int		len;

	*end = s;
	len = 0;
	while (ft_is_set(*s++, set))
		len++;
	if (!*(s - 1))
		return (src_len);
	s += src_len - len - 2;
	while (ft_is_set(*s--, set))
		len++;
	*end = s + 2;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*end;
	char		*result;
	int			len;
	int			i;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc((len - ft_trim_len(s1, set, len, &end) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (ft_is_set(*s1, set))
		s1++;
	while (s1 < end)
		result[i++] = *s1++;
	result[i] = '\0';
	return (result);
}
