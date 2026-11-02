/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:22:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 10:58:54 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo_structs.h"

/* FUNCTIONS */
int		_atoi(const char *str);
void	print_usage(void);
int		print_error(const char *str);
void	print_status(t_philo *philo, const char *status);
void	color_prefix(int id);
size_t	_strlen(const char *str);
time_t	current_time_ms(void);

#endif
