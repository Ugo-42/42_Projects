/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:04:14 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 13:00:45 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* Libft */
# include "libft_allocation.h"
# include "libft_count.h"
# include "libft_print.h"
# include "libft_read.h"
# include "libft_string.h"

/* Standard Libs */
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

# define PROG_NAME "pipex"
# define HERE_DOC_FILE ".here_doc.tmp"

typedef struct s_io_fd
{
	int	input;
	int	output;
}	t_io_fd;

int		ft_execute_command(char *cmd, char **envp);

char	*ft_get_command_path(char *cmd, char **envp);

void	ft_close_pipes(int ***pipes, int pipe_number);
void	ft_exit_error(int exit_code, char *info);
void	ft_free_pipes(int ***pipes, int pipe_number);
void	ft_handle_here_doc(char **argv, char *limiter);
void	ft_open_files(t_io_fd *files, char *input, char *output);
void	ft_open_pipes(int ***pipes, int pipe_number);
void	ft_pipex(size_t nb_cmd, size_t cmd_start, char **argv, char **envp);

#endif
