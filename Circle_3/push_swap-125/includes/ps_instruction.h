/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:38:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/12 11:13:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_INSTRUCTION_H
# define PS_INSTRUCTION_H

/* Push Instructions */
void		ft_push_a(t_cstack *a, t_cstack *b, t_instruction *instructions);
void		ft_push_b(t_cstack *b, t_cstack *a, t_instruction *instructions);

/* Rotate Instructions */
void		ft_rotate_a(t_cstack *a, t_instruction *instructions);
void		ft_rotate_ab(t_cstack *a, t_cstack *b, t_instruction *instructions);
void		ft_rotate_b(t_cstack *b, t_instruction *instructions);

/* Reverse Rotate Instructions */
void		ft_reverse_rotate_a(t_cstack *a, t_instruction *instructions);
void		ft_reverse_rotate_ab(t_cstack *a, t_cstack *b, t_instruction *i);
void		ft_reverse_rotate_b(t_cstack *b, t_instruction *instructions);

/* Swap Instructions */
void		ft_swap_a(t_cstack *a, t_instruction *instructions);
void		ft_swap_ab(t_cstack *a, t_cstack *b, t_instruction *instructions);
void		ft_swap_b(t_cstack *b, t_instruction *instructions);

#endif
