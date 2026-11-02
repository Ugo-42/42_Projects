/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/21 10:49:26 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CLEANUP_H
# define LIBFT_CLEANUP_H

/*┌──────────┐
  │ cleanup/ │
  └──────────┘*/

/**
 * @brief Exits the program after performing a cleanup operation.
 *
 * This function allows you to perform a cleanup operation (e.g., freeing memory)
 * before exiting the program with a specified exit code.
 *
 * @param exit_code The exit code to return to the operating system.
 * @param clean_ft A pointer to the cleanup function to execute.
 * @param clean_arg A pointer to the argument to pass to the cleanup function.
 */
void	ft_cexit(int exit_code, void (*clean_ft)(void *), void *clean_arg);

#endif
