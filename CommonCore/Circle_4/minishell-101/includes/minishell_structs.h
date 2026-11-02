/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 14:18:22 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef enum e_type
{
	ARGUMENT,
	COMMAND,
	FILENAME,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}	t_type;

typedef struct s_env
{
	char	**envp;
	size_t	nb_env;
	size_t	size;
	size_t	total_bytes;
}	t_env;

typedef struct s_commands
{
	char	**cmd;
	size_t	nb_cmd;
}	t_commands;

typedef struct s_redirec
{
	char	**redi;
	t_type	*type;
	size_t	nb_redi;
}	t_redirec;

typedef struct s_heredoc
{
	char	*delimiter;
	int		fd;
	bool	expansion;
}	t_heredoc;

typedef struct s_fd
{
	int	in;
	int	out;
	int	std_in;
	int	std_out;
}	t_fd;

typedef struct t_shell
{
	t_redirec	*redirections;
	t_commands	*commands;
	int			**pipe_fd;
	char		*input;
	t_type		*types;
	char		**token;
	size_t		nb_tokens;
	t_heredoc	*heredocs;
	size_t		curr_heredoc;
	t_env		env;
	t_fd		fd;
	int			exit_code;
}	t_shell;

typedef struct s_command
{
	char	*name;
	void	(*func)(t_shell *shell, char **cmd);
}	t_command;

#endif
