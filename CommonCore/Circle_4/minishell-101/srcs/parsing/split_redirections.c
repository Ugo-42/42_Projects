/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:38:42 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/28 12:29:03 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_redi_nb(t_shell *shell, size_t *i)
{
	size_t		count;

	count = 0;
	if (!shell->token)
		return (0);
	while (shell->token[*i] && shell->types[*i] != PIPE)
	{
		if (shell->types[*i] == REDIR_IN || shell->types[*i] == REDIR_OUT
			|| shell->types[*i] == REDIR_APPEND || shell->types[*i] == HEREDOC
			|| shell->types[*i] == FILENAME)
			count++;
		*i += 1;
	}
	if (shell->token[*i] && shell->types[*i] == PIPE)
		*i += 1;
	return (count);
}

static void	create_redirections(t_shell *shell)
{
	size_t	i;
	size_t	j;
	size_t	nb_redi;

	i = 0;
	j = 0;
	while (j < shell->commands->nb_cmd)
	{
		nb_redi = get_redi_nb(shell, &i);
		shell->redirections[j].type
			= ft_calloc(nb_redi + 1, sizeof (t_type));
		shell->redirections[j].redi
			= ft_calloc(nb_redi + 1, sizeof (char *));
		if (!shell->redirections->redi || !shell->redirections->type)
		{
			while (--j > 0)
			{
				ft_free_null(shell->redirections[j].type);
				ft_free_null(shell->redirections[j].redi);
			}
			ft_cexit_error(1, INTERR "allocation failed", cleanup, shell);
		}
		shell->redirections[j].nb_redi = nb_redi;
		j++;
	}
}

static void	copy_redi(t_shell *shell, t_redirec *red, size_t *i)
{
	size_t		j;

	j = 0;
	while (shell->token[*i] && shell->types[*i] != PIPE)
	{
		if (shell->types[*i] == REDIR_IN || shell->types[*i] == REDIR_OUT
			|| shell->types[*i] == REDIR_APPEND || shell->types[*i] == HEREDOC
			|| shell->types[*i] == FILENAME)
		{
			red->type[j] = shell->types[*i];
			red->redi[j] = ft_strdup(shell->token[*i]);
			if (!red->redi[j])
			{
				while (--j > 0)
					ft_free_null(shell->redirections->redi[j]);
				ft_cexit_error(1, INTERR "allocation failed", cleanup, shell);
			}
			j++;
		}
		*i += 1;
	}
	red->redi[j] = NULL;
	if (shell->token[*i] && shell->types[*i] == PIPE)
		*i += 1;
}

void	split_redirections(t_shell *shell)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	nb_redi;

	if (!shell->token)
		return ;
	k = 0;
	nb_redi = get_redi_nb(shell, &k);
	shell->redirections
		= ft_calloc((shell->commands->nb_cmd + 1), sizeof(t_redirec));
	if (!shell->redirections)
		ft_cexit_error(1, INTERR "allocation failed", cleanup, shell);
	shell->redirections->nb_redi = nb_redi;
	create_redirections(shell);
	i = 0;
	j = 0;
	while (i < shell->commands->nb_cmd)
	{
		copy_redi(shell, &shell->redirections[i], &j);
		i++;
	}
}
