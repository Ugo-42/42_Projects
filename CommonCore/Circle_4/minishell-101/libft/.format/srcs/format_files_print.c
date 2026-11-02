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

void	print_first_line(const char *line1, const char *line2, int total_lines)
{
	if (total_lines < 2)
		printf("SRCS = %s\n", line1);
	else
	{
		if (total_lines > 2)
			printf("SRCS = %-*s%s \\\n", SECOND_PAD, line1, line2);
		else
			printf("SRCS = %-*s%s\n", SECOND_PAD, line1, line2);
	}
}

void	print_subsequent_lines(const char *line1, const char *line2,
		int total_lines, bool last_line)
{
	if (!last_line)
		printf("%*s%-*s%s \\\n", FIRST_PAD, "", SECOND_PAD, line1, line2);
	else
	{
		if (total_lines % 2 == 0)
			printf("%*s%-*s%s\n", FIRST_PAD, "", SECOND_PAD, line1, line2);
		else
			printf("%*s%s\n", FIRST_PAD, "", line1);
	}
}
