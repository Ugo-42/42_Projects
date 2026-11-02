/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:57:19 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/05 13:49:46 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_valid_command(const char *cmd, char **paths)
{
	char	*full_path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_stringf("%s/%s", paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0 && !is_directory(full_path))
		{
			ft_free_2d_char_array(&paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_2d_char_array(&paths);
	return (NULL);
}

char	*get_command_path(const char *cmd, char **envp, t_shell *shell)
{
	char		**paths;
	const char	*path_env;

	if (!cmd || !*cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0 && !is_directory(cmd))
		return (ft_strdup(cmd));
	path_env = get_env_var("PATH", envp, shell);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (find_valid_command(cmd, paths));
}
