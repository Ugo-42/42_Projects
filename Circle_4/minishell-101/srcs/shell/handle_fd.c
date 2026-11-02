/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:58:54 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/22 16:01:56 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open(t_shell *shell)
{
	shell->fd.std_in = dup(STDIN_FILENO);
	shell->fd.std_out = dup(STDOUT_FILENO);
	if (shell->fd.std_in == -1 || shell->fd.std_out == -1)
		ft_cexit_error(1, INTERR "dup err", cleanup, &shell);
	shell->fd.in = STDIN_FILENO;
	shell->fd.out = STDOUT_FILENO;
}

void	handle_close(t_shell *shell)
{
	if (dup2(shell->fd.std_in, STDIN_FILENO) == -1)
		ft_cexit_error(1, INTERR "dup2 err", cleanup, &shell);
	if (dup2(shell->fd.std_out, STDOUT_FILENO) == -1)
		ft_cexit_error(1, INTERR "dup2 err", cleanup, &shell);
	ft_close_null(&shell->fd.std_in);
	ft_close_null(&shell->fd.std_out);
}
