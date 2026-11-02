/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:10 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/26 09:22:16 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format_files.h"

static void	process_file(FILE *file, int total_lines)
{
	char	line1[256];
	char	line2[256];
	int		current_line;

	current_line = 0;
	current_line += read_line_pair(file, line1, line2);
	print_first_line(line1, line2, total_lines);
	while (current_line < total_lines)
	{
		current_line += read_line_pair(file, line1, line2);
		print_subsequent_lines(line1, line2, total_lines,
			current_line == total_lines);
	}
}

int	main(void)
{
	FILE	*file;
	int		total_lines;

	file = fopen(".files", "r");
	if (!file)
	{
		perror("Failed to open `" FILE_PATH "` for reading");
		return (1);
	}
	total_lines = count_lines(file);
	printf("# Functions: %d\n", total_lines);
	rewind(file);
	process_file(file, total_lines);
	fclose(file);
	return (0);
}
