/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_skip.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/05 15:28:39 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SKIP_H
# define LIBFT_SKIP_H

/* skip/ */

int		ft_skip_quoted(const char **str);

void	ft_skip_chars(const char **str, const char c);
void	ft_skip_not_chars(const char **str, const char c);
void	ft_skip_spaces(const char **str);
void	ft_skip_word(const char **str);

#endif
