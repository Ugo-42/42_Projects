/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_pipes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:45:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/03 15:20:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_pipes(int ***pipes, int pipe_number)
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

void	ft_close_pipes(int ***pipes, int pipe_number)
{
	if (!pipes || !*pipes)
		return ;
	while (--pipe_number >= 0)
	{
		close((*pipes)[pipe_number][0]);
		close((*pipes)[pipe_number][1]);
	}
}

void	ft_open_pipes(int ***pipes, int pipe_number)
{
	int	i;

	*pipes = malloc(pipe_number * sizeof(int *));
	if (!*pipes)
		ft_exit_error(1, "malloc");
	i = 0;
	while (i < pipe_number)
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!(*pipes)[i])
		{
			ft_close_pipes(pipes, i);
			ft_free_pipes(pipes, i);
			ft_exit_error(1, "malloc");
		}
		if (pipe((*pipes)[i]) == -1)
		{
			ft_close_pipes(pipes, i);
			ft_free_pipes(pipes, i + 1);
			ft_exit_error(1, "pipe");
		}
		i++;
	}
}
