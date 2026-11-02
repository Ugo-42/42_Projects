/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:39:03 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/23 11:27:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROMPT_H
# define MINISHELL_PROMPT_H

# define RED            "\1\033[38;2;255;0;0m\2"
# define MAGENTA        "\1\033[38;2;255;0;255m\2"
# define INDIGO         "\1\033[38;2;102;0;255m\2"
# define WHITE          "\1\033[38;2;255;255;255m\2"

# define HEREDOC_PROMPT "\1\033[38;2;96;96;96m\2heredoc> \1\033[0m\2"

# define HOSTNAME       "minishell"

#endif
