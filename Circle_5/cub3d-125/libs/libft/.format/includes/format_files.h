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

#ifndef FORMAT_FILES_H
# define FORMAT_FILES_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>

# define FILE_PATH ".files"

/** max filename size **/
# define BUF_SIZE 256

/*** Column Padding ***/
# define FIRST_PAD  7
# define SECOND_PAD 40

/* PRINT FUNCTIONS */
void	print_first_line(const char *line1, const char *line2, int total_lines);

void	print_subsequent_lines(const char *line1, const char *line2,
			int total_lines, bool last_line);

/* UTILS */
int		count_lines(FILE *file);
int		read_line_pair(FILE *file, char *line1, char *line2);

#endif
