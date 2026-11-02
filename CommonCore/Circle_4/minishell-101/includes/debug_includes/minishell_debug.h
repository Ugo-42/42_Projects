/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_debug.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:34:06 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/30 09:43:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEBUG_H
# define MINISHELL_DEBUG_H

# define ALWAYS_PRINT 0
# define BLOCK_COMMANDS 0

/* Colors */
# define TURQUOISE   0x50BFBF
# define BRICK_RED   0xC4422C
# define OLIVE_GREEN 0x99C050
# define BLUE        0x3C77C3
# define PURPLE      0x8820A0
# define ORANGE      0xFF4D00
# define YELLOW      0xFFA500

/* Print Func */
void	___debug___(const char *title, const char *value, uint32_t color);
void	___debug_2d___(const char *title, char **array, uint32_t color);
void	___debug_type___(const char *title, char **token, t_type *types,
			uint32_t color);
void	___debug_commands___(t_commands *cmds, uint32_t color);
void	___debug_redirections___(t_redirec *redirections, uint32_t color);

#endif
