/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:53:52 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/18 13:49:18 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_lock, NULL) != 0
		|| pthread_mutex_init(&data->end_mutex, NULL) != 0
		|| pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (false);
	i = 0;
	while (i < data->args.philos_nb)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (false);
	}
	return (true);
}

void	init_philos(t_data *data)
{
	const int	philos_nb = data->args.philos_nb;
	int			i;

	i = 0;
	while (i < philos_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % philos_nb];
		data->philos[i].data = data;
		i++;
	}
}

bool	init_data(t_data *data)
{
	data->forks = malloc(data->args.philos_nb * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		return (!print_error("Allocation failed."));
	}
	data->philos = malloc(data->args.philos_nb * sizeof(t_philo));
	if (!data->philos)
	{
		free(data->forks);
		return (!print_error("Allocation failed."));
	}
	memset(data->philos, 0, data->args.philos_nb * sizeof(t_philo));
	if (!init_mutex(data))
	{
		free(data->forks);
		free(data->philos);
		return (!print_error("Mutex init."));
	}
	data->start_time = current_time_ms();
	init_philos(data);
	data->simulation_end = false;
	return (true);
}
