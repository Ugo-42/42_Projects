/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:49:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/09 11:48:10 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_shell *shell, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = expand_env_vars(shell->env.envp, tokens[i], shell);
		if (!tokens[i])
		{
			if (tokens[i + 1])
			{
				while (tokens[++i])
					ft_free_null(&tokens[i]);
			}
			ft_free_2d_char_array(&tokens);
			ft_putstr_nl_fd(2, INTERR "Failed to expand env var.");
			return ;
		}
		i++;
	}
}
