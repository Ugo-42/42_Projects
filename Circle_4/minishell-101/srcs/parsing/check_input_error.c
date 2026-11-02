/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:47:36 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/30 11:47:37 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_unclosed_quotes(char *input)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	return (quote != 0);
}

void	check_input_error(t_shell *shell)
{
	size_t	i;

	if (!shell->input)
	{
		ft_putstr_nl_fd(2, PERR "Error while parsing");
		return ;
	}
	i = 0;
	while (ft_is_space(shell->input[i]))
		i++;
	if (!shell->input[i])
		return ;
	if (check_unclosed_quotes(shell->input))
	{
		ft_putstr_nl_fd(2, PERR "Unclosed quotes >:(");
		return ;
	}
}
