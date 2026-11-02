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

int	count_lines(FILE *file)
{
	char	buffer[256];
	int		lines;

	lines = 0;
	while (fgets(buffer, sizeof(buffer), file))
		lines++;
	return (lines);
}

int	read_line_pair(FILE *file, char *line1, char *line2)
{
	if (!fgets(line1, BUF_SIZE, file))
	{
		line1[0] = '\0';
		return (0);
	}
	line1[strcspn(line1, "\n")] = '\0';
	if (!fgets(line2, BUF_SIZE, file))
	{
		line2[0] = '\0';
		return (1);
	}
	line2[strcspn(line2, "\n")] = '\0';
	return (2);
}
