/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:04 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 14:33:01 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open_files(t_io_fd *files, char *input, char *output)
{
	int	exit_code;
	int	o_mode;

	o_mode = O_TRUNC;
	if (ft_strcmp(input, HERE_DOC_FILE) == 0)
		o_mode = O_APPEND;
	exit_code = 0;
	files->input = open(input, O_RDONLY);
	if (files->input == -1)
	{
		ft_fprintf(2, "%s: %s: %s\n", PROG_NAME, strerror(errno), input);
		exit_code |= 1;
	}
	files->output = open(output, O_WRONLY | O_CREAT | o_mode, 0644);
	if (files->output == -1)
	{
		if (files->input != -1)
			close(files->input);
		ft_fprintf(2, "%s: %s: %s\n", PROG_NAME, strerror(errno), output);
		exit_code |= 2;
	}
	if (exit_code == 1)
		close(files->output);
	if (exit_code)
		exit(exit_code);
}
