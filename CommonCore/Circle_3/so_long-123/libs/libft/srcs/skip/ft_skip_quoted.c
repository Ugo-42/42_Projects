/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:49:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/05 14:49:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_skip_quoted(const char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (**str != quote)
	{
		return (-1);
	}
	(*str)++;
	return (0);
}
