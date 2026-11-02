/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/26 14:41:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ERROR_H
# define LIBFT_ERROR_H

# include <stdbool.h>

/*┌────────┐
  │ error/ │
  └────────┘*/

# define BAD_ARG    "invalid argument(s)."
# define BAD_OPEN   "couldn't open file."
# define BAD_ALLOC  "allocation failed."
# define BAD_BAD    "unexpected error."

/**
 * @brief Exits the program with an error message.
 * @param exit_code The exit code to return to the operating system.
 * @param error_msg The error message to display.
 */
void	ft_exit_error(int exit_code, char *error_msg);

/**
 * @brief Exits the program with and free the error message.
 * @param exit_code The exit code to return to the operating system.
 * @param error_msg The error message to display.
 */
void	ft_fexit_error(int exit_code, char *error_msg);

/**
 * @brief Exits the program with an error message after performing cleanup.
 * @param exit_code The exit code to return to the operating system.
 * @param error_msg The error message to display.
 * @param clean_ft A pointer to the cleanup function to execute.
 * @param clean_arg A pointer to the argument to pass to the cleanup function.
 */
void	ft_cexit_error(int exit_code, char *error_msg,
			void (*clean_ft)(void *), void *clean_arg);

/**
 * @brief Exits the program with an error message after performing
 *        cleanup and frees the error message.
 * @param exit_code The exit code to return to the operating system.
 * @param error_msg The error message to display.
 * @param clean_ft A pointer to the cleanup function to execute.
 * @param clean_arg A pointer to the argument to pass to the cleanup function.
 */
void	ft_fcexit_error(int exit_code, char *error_msg,
			void (*clean_ft)(void *), void *clean_arg);

#endif
