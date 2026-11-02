/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:58:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 13:58:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	size_t	nb_cmd;
	size_t	cmd_start;

	if (argc < 5)
	{
		ft_fprintf(2, "Usage: %s file1 cmd1 cmd2 ... file2\n", argv[0]);
		ft_fprintf(2, "   OR: %s here_doc LIMITER cmd1 ... file\n", argv[0]);
		return (1);
	}
	nb_cmd = argc - 3;
	cmd_start = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		ft_handle_here_doc(argv, argv[2]);
		nb_cmd = argc - 4;
		cmd_start = 3;
	}
	ft_pipex(nb_cmd, cmd_start, argv, envp);
	if (ft_strcmp(argv[1], HERE_DOC_FILE) == 0)
		unlink(argv[1]);
	return (0);
}
