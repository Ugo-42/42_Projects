/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:40:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/15 09:58:49 by ugwentzi         ###   ########.fr       */
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

static void	handle_quotes(t_flexistr *fs, t_qstate *qs, t_input *input)
{
	if (input->str[input->i] == '\'')
	{
		if (!qs->in_dquote)
			qs->in_squote = !qs->in_squote;
		if (qs->in_dquote)
			fs_n_append(fs, "'", 1);
		input->i++;
	}
	else if (input->str[input->i] == '"')
	{
		if (!qs->in_squote)
			qs->in_dquote = !qs->in_dquote;
		if (qs->in_squote)
			fs_n_append(fs, "\"", 1);
		input->i++;
	}
}

static void	handle_expansion(t_flexistr *fs, t_qstate *qs, t_input *input,
	t_shell *shell)
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
		if (!qs->in_squote)
		{
			value = ft_strdup(get_env_var(varname, shell->env.envp, shell));
			free(varname);
		}
		else
		{
			fs_append(fs, "$", false);
			value = varname;
		}
	}
	input->i += len;
	fs_append(fs, value, true);
}

char	*expand_env_vars(char **envp, char *shell_input, t_shell *shell)
{
	size_t		len;
	t_flexistr	fs;
	t_qstate	qs;
	t_input		input;

	if (!envp || !shell_input || fs_init(&fs, 64) != 0)
		return (NULL);
	input = (t_input){shell_input, 0};
	qs = (t_qstate){0};
	while (input.str[input.i])
	{
		len = ft_strcspn(input.str + input.i, "\"'$");
		if (fs_n_append(&fs, input.str + input.i, len) == -1)
			return (NULL);
		input.i += len;
		if (!input.str[input.i])
			break ;
		if (input.str[input.i] == '$')
			handle_expansion(&fs, &qs, &input, shell);
		else
			handle_quotes(&fs, &qs, &input);
		if (!fs.string)
			return (NULL);
	}
	return (free(shell_input), fs_finalize(&fs));
}
