/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:18:11 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/09 09:15:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_prompt.h"

#include <stddef.h>

static const char	*get_glitch_user(void)
{
	static const char	*strings[] = {
		"u$3r", "us#r", "Ʉ$€Я", "🆄 🆂 🅴 🆁 ", "u͟s͟e͟r͟", "µ§Ω¤½!", "ÿΘΣ♀░╩",
		"≈∞∑≈Ω≡", "∂⌘∩Ω↑", "≠≈░†ÿ", "U¤℮⌐⊗", "NULL", "UNKNOWN", "notfound",
		"llehsinim", "root", "404", "0x7fff2a34de", "segfault", "void",
		"mini🐚", "Mini🪑>", "jpeter", "lrieffel", "nduvoid", "tquessad",
		"line 2457: syntax error", "???", ":(){:|:};:", "¯\\_(ツ)_/¯", "🚫",
		"SIGSEGV", "shrek", "amogus", "/dev/null", "(core dumped)", "bocal"
	};
	const size_t		count = sizeof(strings) / sizeof(strings[0]);
	const char			*glitched_string = strings[ft_random() % count];

	return (glitched_string);
}

static const char	*get_username(char **envp, t_shell *shell)
{
	const char	*user = get_env_var("USER", envp, shell);

	if (!user || ft_strnlen(user, CHAR_MAX) >= CHAR_MAX)
		user = get_glitch_user();
	return (user);
}

static char	*get_display_path(char **envp, t_shell *shell)
{
	const char	*home;
	char		*cwd;
	char		*display_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("?"));
	home = get_env_var("HOME", envp, shell);
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		display_path = ft_stringf("~%s", cwd + ft_strlen(home));
	else
		display_path = ft_strdup(cwd);
	free(cwd);
	return (display_path);
}

static char	*update_prompt(char **envp, t_shell *shell)
{
	const char	*user;
	char		*display_path;
	char		*prompt;

	user = get_username(envp, shell);
	display_path = get_display_path(envp, shell);
	prompt = ft_stringf(RED "%s@" HOSTNAME MAGENTA ":" INDIGO "%s"
			MAGENTA "$" WHITE " ", user, display_path);
	free(display_path);
	return (prompt);
}

void	display_prompt(t_shell *shell)
{
	char	*prompt;

	prompt = update_prompt(shell->env.envp, shell);
	if (!prompt)
		prompt = "user@" HOSTNAME "$ ";
	if (shell->input)
		ft_free_null(&shell->input);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		shell->input = readline(prompt);
	if (shell->input && *shell->input)
		add_history(shell->input);
	free(prompt);
}
