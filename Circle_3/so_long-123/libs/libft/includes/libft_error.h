/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
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

# ifndef FANCY
#  define FANCY 0
# endif

# define BAD_ARG	"invalid argument(s)."
# define BAD_OPEN	"couldn't open file."
# define BAD_ALLOC	"allocation failed."
# define BAD_BAD	"unexpected error."

void	ft_fwarning(char *error_msg);
void	ft_warning(char *error_msg);
void	ft_exit_error(int exit_code, char *error_msg);
void	ft_fexit_error(int exit_code, char *error_msg);

void	ft_cexit_error(int exit_code, char *error_msg,
			void (*clean_ft)(void *), void *clean_arg);

void	ft_fcexit_error(int exit_code, char *error_msg,
			void (*clean_ft)(void *), void *clean_arg);

#endif
