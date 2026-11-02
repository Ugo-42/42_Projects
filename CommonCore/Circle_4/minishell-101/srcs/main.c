/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:13:51 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/05 16:47:35 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	handle_signal();
	while (1)
	{
		handle_open(&shell);
		display_prompt(&shell);
		if (!shell.input)
		{
			ft_putstr_nl("exit");
			ft_cexit(0, cleanup, &shell);
		}
		if (!*shell.input)
		{
			handle_close(&shell);
			continue ;
		}
		parse_input(&shell);
		handle_close(&shell);
	}
}
