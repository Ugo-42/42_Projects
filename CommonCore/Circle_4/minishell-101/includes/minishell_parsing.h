/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:39:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/21 10:39:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

typedef struct s_input
{
	char	*str;
	size_t	i;
}	t_input;

typedef struct s_qstate
{
	bool		in_dquote;
	bool		in_squote;
}	t_qstate;

typedef struct s_assign_type
{
	size_t	i;
	size_t	j;
	bool	is_command;
}	t_assign_type;

#endif
