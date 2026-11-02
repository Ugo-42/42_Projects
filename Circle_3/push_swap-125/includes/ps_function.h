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

#ifndef PS_FUNCTION_H
# define PS_FUNCTION_H

/* Main Functions */
void		ft_int_limited(char **numbers);
void		ft_check_valid_stack(char **stack);
void		ft_push_swap(size_t nb_numbers, char **numbers);

/* Algorithm */
void		ft_pre_sort(t_cstack *a, t_cstack *b, t_instruction *i,
				t_magic_value magic);
void		ft_push_back(t_cstack *a, t_cstack *b, t_instruction *i);
void		ft_sort_three(t_cstack *a, t_instruction *i);

void		ft_combine(t_instruction *i);
void		ft_print_instruction(t_instruction *i);
void		ft_write_instruction(t_instruction *i,
				enum e_instructions instruction);

/* Init Functions */
int			ft_init_stacks(t_cstack *a, t_cstack *b,
				size_t nb_numbers, char **numbers);

void		ft_init_instructions(t_instruction *instructions);
void		ft_init_percentiles(t_percentile *p, t_cstack *a);
void		ft_init_magic(t_magic_value *magic, size_t nb_numbers);

t_three_nb	ft_init_three_nb(t_cstack *a);
t_three_cmp	ft_init_three_cmp(t_three_nb three);

/* Helper Functions */
int			ft_cmp_nb(const void *a, const void *b);
int			cmp(const char *a, const char *b);
void		ft_swap_char_address(char **a, char **b);

#endif
