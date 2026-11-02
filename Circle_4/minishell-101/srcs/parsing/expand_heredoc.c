/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:22:53 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/05 15:29:08 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

static size_t	count_varlen(const char *input)
{
	size_t	len;

	if (input && *input == '?')
		return (1);
	len = 0;
	while (input[len] && ((ft_is_alnum(input[len]) || input[len] == '_')))
		len++;
	return (len);
}

static void	handle_expansion(t_flexistr *fs, t_input *input, t_shell *shell)
{
	char	*varname;
	char	*value;
	size_t	len;

	len = count_varlen(input->str + ++input->i);
	if (len == 0)
		value = ft_strdup("$");
	else
	{
		varname = ft_strndup(input->str + input->i, len);
		value = ft_strdup(get_env_var(varname, shell->env.envp, shell));
		free(varname);
	}
	input->i += len;
	fs_append(fs, value, true);
}

char	*expand_heredoc(t_shell *shell, char *heredoc)
{
	t_flexistr	fs;
	t_input		input;
	size_t		len;

	if (!shell->env.envp || !heredoc || fs_init(&fs, 64) != 0)
		return (NULL);
	input = (t_input){heredoc, 0};
	while (input.str[input.i])
	{
		len = ft_strcspn(input.str + input.i, "$");
		if (fs_n_append(&fs, input.str + input.i, len) == -1)
			return (NULL);
		input.i += len;
		if (!input.str[input.i])
			break ;
		handle_expansion(&fs, &input, shell);
		if (!fs.string)
			return (NULL);
	}
	return (free(heredoc), fs_finalize(&fs));
}
