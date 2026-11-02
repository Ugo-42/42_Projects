/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:16 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:10:11 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_prompt.h"

static void	print(int fd, const char *str)
{
	if (fd == -1)
		return ;
	if (str == NULL)
	{
		write(fd, "\n", 1);
		return ;
	}
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

size_t	get_heredoc_number(char **token)
{
	size_t	heredoc_number;
	size_t	i;

	heredoc_number = 0;
	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "<<") == 0)
			heredoc_number++;
		i++;
	}
	return (heredoc_number);
}

static bool	process_heredoc(t_shell *shell, t_heredoc *here, size_t i, int out)
{
	char			*input;
	const size_t	len_del = ft_strlen(here->delimiter);

	input = readline(HEREDOC_PROMPT);
	if (!isatty(STDIN_FILENO))
		return (false);
	if (input == NULL)
	{
		ft_fprintf(2, PERR "warning: heredoc at line %i delimited by"
			" end-of-file (wanted `%s')\n", i, here->delimiter);
		return (false);
	}
	if (ft_strncmp(input, here->delimiter, len_del) == 0
		&& input[len_del] == '\0')
	{
		free(input);
		return (false);
	}
	if (here->expansion)
		input = expand_heredoc(shell, input);
	print(out, input);
	free(input);
	return (true);
}

void	handle_heredoc(t_shell *shell)
{
	size_t	heredoc_number;
	size_t	i;
	size_t	j;
	int		pipefd[2];

	heredoc_number = get_heredoc_number(shell->token);
	if (heredoc_number == 0)
		return ;
	i = 0;
	while (i < heredoc_number && isatty(STDIN_FILENO))
	{
		if (pipe(pipefd) == -1)
			ft_cexit_error(1, INTERR "pipe err", cleanup, shell);
		j = 0;
		while (true)
		{
			if (!process_heredoc(shell, &shell->heredocs[i], j, pipefd[1]))
				break ;
			j++;
		}
		close(pipefd[1]);
		shell->heredocs[i].fd = pipefd[0];
		i++;
	}
	shell->curr_heredoc = 0;
}

void	create_heredoc(t_shell *shell)
{
	size_t	heredoc_number;

	heredoc_number = get_heredoc_number(shell->token);
	if (heredoc_number == 0)
		return ;
	shell->heredocs = ft_calloc(sizeof (t_heredoc), heredoc_number + 1);
	if (!shell->heredocs)
		ft_cexit_error(1, "allocation failed", cleanup, shell);
}
