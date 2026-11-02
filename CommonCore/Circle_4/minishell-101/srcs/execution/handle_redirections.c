/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:38 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/05 15:00:46 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_prompt.h"

static void	open_out(t_shell *shell, char *filename, int write_mode)
{
	int	fd;

	fd = open(filename, O_WRONLY | write_mode | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, PERR "%s: %s\n", filename, strerror(errno));
		shell->exit_code = 1;
		return ;
	}
	ft_close_null(&shell->fd.out);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_cexit_error(1, INTERR "dup2 err", cleanup, shell);
	shell->fd.out = fd;
}

static void	open_in(t_shell *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, PERR "%s: %s\n", filename, strerror(errno));
		shell->exit_code = 1;
		return ;
	}
	ft_close_null(&shell->fd.in);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_cexit_error(1, INTERR "dup2 err", cleanup, shell);
	shell->fd.in = fd;
}

static void	open_heredoc(t_shell *shell)
{
	int	fd;

	fd = shell->heredocs[shell->curr_heredoc].fd;
	ft_close_null(&shell->fd.in);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_cexit_error(1, INTERR "dup2 err", cleanup, shell);
	shell->fd.in = dup(fd);
	if (shell->fd.in == -1)
		ft_cexit_error(1, INTERR "dup err", cleanup, shell);
	shell->curr_heredoc++;
}

bool	handle_redirections(t_shell *shell, t_redirec *redir)
{
	size_t	i;

	shell->exit_code = 0;
	if (redir->nb_redi == 0)
		return (true);
	i = 0;
	while (redir->redi[i])
	{
		if (redir->type[i] == REDIR_IN)
			open_in(shell, redir->redi[i + 1]);
		else if (redir->type[i] == REDIR_OUT)
			open_out(shell, redir->redi[i + 1], O_TRUNC);
		else if (redir->type[i] == REDIR_APPEND)
			open_out(shell, redir->redi[i + 1], O_APPEND);
		else if (redir->type[i] == HEREDOC)
			open_heredoc(shell);
		if (shell->exit_code != 0)
			return (false);
		i += 2;
	}
	return (true);
}
