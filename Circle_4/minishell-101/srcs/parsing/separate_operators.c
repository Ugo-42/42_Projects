/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:41:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 14:30:12 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

void	handle_operator(t_flexistr *fs, t_input *input)
{
	const char	operator = input->str[input->i];
	size_t		op_len;

	if (input->i > 0 && input->str[input->i - 1] != ' ')
		fs_n_append(fs, " ", 1);
	op_len = 1;
	if (operator != '|' && input->str[input->i + 1] == operator)
		op_len = 2;
	fs_n_append(fs, input->str + input->i, op_len);
	input->i += op_len;
	if (input->str[input->i] && !is_operator_single(&input->str[input->i])
		&& input->str[input->i] != ' ')
	{
		fs_n_append(fs, " ", 1);
	}
}

static bool	handle_quotes(t_flexistr *fs, t_input *input, size_t len)
{
	const size_t	start = len + input->i;
	const char		quote[] = {input->str[start], '\0'};

	if (*quote == '\'' || *quote == '\"')
	{
		len += ft_strcspn(&input->str[start + 1], quote) + 2;
		if (!input->str[len + input->i - 1])
			return (false);
		if (fs_n_append(fs, input->str + input->i, len) == -1)
			return (false);
		input->i += len;
		return (true);
	}
	return (false);
}

char	*separate_operators(char *shell_input)
{
	size_t		len;
	t_flexistr	fs;
	t_input		input;

	if (!shell_input || fs_init(&fs, 64) != 0)
		return (NULL);
	input = (t_input){shell_input, 0};
	while (input.str[input.i])
	{
		len = ft_strcspn(input.str + input.i, "<>|\'\"");
		if (handle_quotes(&fs, &input, len))
			continue ;
		if (fs_n_append(&fs, input.str + input.i, len) == -1)
			return (NULL);
		input.i += len;
		if (!input.str[input.i])
			break ;
		handle_operator(&fs, &input);
		if (!fs.string)
			return (NULL);
	}
	return (free(shell_input), fs_finalize(&fs));
}
