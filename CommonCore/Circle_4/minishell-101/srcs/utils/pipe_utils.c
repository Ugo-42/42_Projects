/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:21 by vvalenti          #+#    #+#             */
/*   Updated: 2025/04/28 16:34:04 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int ***pipes, int pipe_number)
{
	if (!pipes || !*pipes)
		return ;
	while (--pipe_number >= 0)
	{
		free((*pipes)[pipe_number]);
		(*pipes)[pipe_number] = NULL;
	}
	free(*pipes);
	*pipes = NULL;
}

void	close_pipes(int ***pipes, int pipe_number)
{
	if (!pipes || !*pipes)
		return ;
	while (--pipe_number >= 0)
	{
		close((*pipes)[pipe_number][0]);
		close((*pipes)[pipe_number][1]);
	}
}

void	open_pipes(int ***pipes, int pipe_number)
{
	int	i;

	*pipes = ft_calloc(pipe_number, sizeof(int *));
	if (!*pipes)
		ft_exit_error(1, PERR "allocation failed");
	i = 0;
	while (i < pipe_number)
	{
		(*pipes)[i] = ft_calloc(2, sizeof(int));
		if (!(*pipes)[i])
		{
			close_pipes(pipes, i);
			free_pipes(pipes, i);
			ft_exit_error(1, PERR "allocation failed");
		}
		if (pipe((*pipes)[i]) == -1)
		{
			close_pipes(pipes, i);
			free_pipes(pipes, i + 1);
			ft_exit_error(1, PERR "pipe creation failed");
		}
		i++;
	}
}
