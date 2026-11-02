/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:22:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/18 13:50:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_FUNCTIONS_H
# define PHILO_FUNCTIONS_H

/* FUNCTIONS */
bool		parse_args(t_args *args, int argc, char **argv);
bool		init_data(t_data *data);
void		*routine(void *arg);
void		*grim_reaper(void *arg);
bool		is_simulation_over(t_data *data);

#endif
