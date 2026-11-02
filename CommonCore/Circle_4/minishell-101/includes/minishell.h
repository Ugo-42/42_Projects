/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:14:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/16 15:34:47 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROG "minishell"
# define PERR "minishell: "
# define INTERR "minishell: internal error: "

# define ARG_MAX 2097152

/* HEADERS */
# include "libft.h"
# include "minishell_structs.h"
# include "minishell_functions.h"

/* LIBS */
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <wait.h>

#endif
