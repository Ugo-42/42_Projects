/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_read.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:09:23 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/05 14:25:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_READ_H
# define LIBFT_READ_H

/*┌───────┐
  │ read/ │
  └───────┘*/

/**
 * @brief Resets the state of a file descriptor used by get_next_line.
 *
 * This function clears any internal buffers or states associated with the
 * specified file descriptor, ensuring that subsequent calls to
 * `get_next_line` start fresh.
 *
 * @param fd The file descriptor to reset.
 */
void		gnl_reset_fd(int fd);

/**
 * @brief Reads the next line from a file descriptor.
 *
 * This function reads a single line from the specified file descriptor,
 * including the newline character if present. It dynamically allocates
 * memory for the line, which must be freed by the caller.
 *
 * @param fd The file descriptor to read from.
 * @return A pointer to the next line, or NULL if the end of the file is
 *         reached or an error occurs.
 */
char		*get_next_line(int fd);

#endif
