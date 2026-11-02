/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vstringf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:23:27 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 12:05:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VSTRINGF_H
# define FT_VSTRINGF_H

/*┌──────────────┐
  │ ft_stringf.c │
  └──────────────┘*/

# include <stdint.h>

void	internal_append_ptr(t_flexistr *fs, uintptr_t addr);
void	internal_append_str(t_flexistr *fs, char *s);

void	internal_pad(t_flexistr *fs, size_t pad_len, size_t index);
void	internal_pad_middle(t_flexistr *fs, size_t pad_len, size_t left_index);

void	internal_append_color(t_flexistr *fs, const char format,
			uint32_t color);

#endif
