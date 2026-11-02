/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:58:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/06 09:49:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	size_t	nb_cmd;
	size_t	cmd_start;

	if (argc != 5)
	{
		ft_fprintf(2, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (1);
	}
	nb_cmd = argc - 3;
	cmd_start = 2;
	ft_pipex(nb_cmd, cmd_start, argv, envp);
	return (0);
}
