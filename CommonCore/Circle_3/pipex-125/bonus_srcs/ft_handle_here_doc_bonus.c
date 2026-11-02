/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_here_doc_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:12:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 11:17:09 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_handle_here_doc(char **argv, char *limiter)
{
	size_t	len;
	char	*line;
	int		fd;

	argv[1] = HERE_DOC_FILE;
	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit_error(1, "open");
	len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd(STDOUT_FILENO, "heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, len) == 0 && line[len] == '\n'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(fd, line);
		free(line);
	}
	close(fd);
}
