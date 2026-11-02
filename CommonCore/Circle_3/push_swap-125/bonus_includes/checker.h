/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:38:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/17 09:57:40 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

/* to limit the program with max int values */
# define INT_LIMITED 1

/* personal libs */
# include "libft.h"

/* standard libs */
# include <unistd.h>

/* Main Functions */
int		ft_cmp_nb(const void *a, const void *b);
int		ft_init_stacks(t_cstack *a, t_cstack *b,
			size_t nb_numbers, char **numbers);
bool	ft_is_valid_instruction(const char *instruction);
void	ft_check_valid_stack(char **numbers);
void	ft_checker(size_t nb_numbers, char **numbers);
void	ft_discard_stdout(void);
void	ft_execute_instruction(t_cstack *a, t_cstack *b, char *instruction);
void	ft_int_limited(char **numbers);
void	ft_swap_char_address(char **a, char **b);

/* Stack Instruction */
void	ft_push_a(t_cstack *a, t_cstack *b);
void	ft_push_b(t_cstack *b, t_cstack *a);
void	ft_reverse_rotate_a(t_cstack *a);
void	ft_reverse_rotate_b(t_cstack *b);
void	ft_reverse_rotate_ab(t_cstack *a, t_cstack *b);
void	ft_rotate_a(t_cstack *a);
void	ft_rotate_b(t_cstack *b);
void	ft_rotate_ab(t_cstack *a, t_cstack *b);
void	ft_swap_a(t_cstack *a);
void	ft_swap_b(t_cstack *b);
void	ft_swap_ab(t_cstack *a, t_cstack *b);

#endif
