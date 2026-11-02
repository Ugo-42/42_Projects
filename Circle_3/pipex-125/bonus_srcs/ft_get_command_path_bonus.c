/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:57:19 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/29 16:25:28 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_get_path_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*ft_find_valid_command(char **paths, char *cmd)
{
	char	*full_path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_str_ultimate_join(paths[i], "/", cmd, NULL);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_2d_array(&paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_2d_array(&paths);
	return (NULL);
}

char	*ft_get_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (ft_find_valid_command(paths, cmd));
}
