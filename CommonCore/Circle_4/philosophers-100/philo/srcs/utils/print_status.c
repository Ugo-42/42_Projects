/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:53:26 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 11:01:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, const char *status)
{
	time_t				timestamp;

	if (is_simulation_over(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = current_time_ms() - philo->data->start_time;
	color_prefix(philo->id);
	printf("%ld %d %s%s\n", timestamp, philo->id, status, RESET_COLOR);
	pthread_mutex_unlock(&philo->data->print_lock);
}
