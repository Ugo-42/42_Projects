/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:09 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 14:16:50 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTIONS_H
# define MINISHELL_FUNCTIONS_H

# include "minishell_structs.h"

/* BUILT_IN/ */
void		exec_binary(t_shell *shell, char **cmd);
void		exec_binary_fork(t_shell *shell, char **cmd);
void		exec_cd(t_shell *shell, char **cmd);
void		exec_echo(t_shell *shell, char **cmd);
void		exec_env(t_shell *shell, char **cmd);
void		exec_exit(t_shell *shell, char **cmd);
void		exec_export(t_shell *shell, char **cmd);
void		exec_pwd(t_shell *shell, char **cmd);
void		exec_unset(t_shell *shell, char **cmd);

/* EXECUTION */
void		command_executor(t_shell *shell, char **cmd);
void		execute_command(t_shell *shell, char **cmd);
void		handle_heredoc(t_shell *shell);
void		handle_pipe(t_shell *shell);
bool		handle_redirections(t_shell *shell, t_redirec *redir);

/* PARSING */
void		assign_types(t_shell *shell, char **cmds);
void		check_input_error(t_shell *shell);
bool		commands_check(t_shell *shell, char **token);
char		*expand_heredoc(t_shell *shell, char *heredoc);
void		expand_tokens(t_shell *shell, char **tokens);
char		*expand_env_vars(char **envp, char *input, t_shell *shell);
void		parse_input(t_shell *shell);
char		*separate_operators(char *input);
void		split_commands(t_shell *shell);
void		split_redirections(t_shell *shell);

/* SHELL */
void		cleanup(void *param);
void		handle_open(t_shell *shell);
void		handle_close(t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		input_cleanup(void *param);
void		display_prompt(t_shell *shell);

/* SIGNAL/ */
void		handle_signal(void);
void		heredoc_signal(void);
void		restore_signal(void);
void		set_signal(int signal, void (*handler)(int));

/* UTILS */
int			convert_exit_status(int status);
char		*get_command_path(const char *cmd, char **envp, t_shell *shell);
const char	*get_env_var(const char *varname, char **envp, t_shell *shell);
bool		is_directory(const char *path);
bool		is_operator(const char *cmd);
bool		is_operator_single(char *input);
bool		is_redirection(const char *cmd);
void		free_pipes(int ***pipes, int pipe_number);
void		close_pipes(int ***pipes, int pipe_number);
void		open_pipes(int ***pipes, int pipe_number);
size_t		get_heredoc_number(char **token);
char		*strdup_reject(const char *src, const char *reject);
void		create_heredoc(t_shell *shell);
bool		in_tty(void);

#endif
