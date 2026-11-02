/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:08:48 by vvalenti          #+#    #+#             */
/*   Updated: 2025/05/09 14:22:07 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

bool	is_operator_single(char *input)
{
	const char	*valid[] = {"<", ">", "|", NULL};
	const char	**op = valid;

	while (*op)
	{
		if (ft_strncmp(input, *op, 1) == 0)
			return (true);
		op++;
	}
	return (false);
}

bool	is_operator(const char *input)
{
	const char	*valid[] = {"<", ">", "|", ">>", "<<", NULL};
	const char	**op = valid;

	while (*op)
	{
		if (ft_strcmp(input, *op) == 0)
			return (true);
		op++;
	}
	return (false);
}

bool	is_redirection(const char *cmd)
{
	const char	*valid[] = {"<", ">", ">>", "<<", NULL};
	const char	**op = valid;

	while (*op)
	{
		if (ft_strcmp(cmd, *op) == 0)
			return (true);
		op++;
	}
	return (false);
}
