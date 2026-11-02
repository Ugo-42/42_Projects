/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:44:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 13:56:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_simulation_over(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

static void	end(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->end_mutex);
}

static void	*death(t_data *data, time_t now, int i)
{
	pthread_mutex_lock(&data->print_lock);
	color_prefix(data->philos[i].id);
	printf(BOLD BLINK "%ld %d died%s\n", now - data->start_time,
		data->philos[i].id, RESET_COLOR);
	pthread_mutex_unlock(&data->print_lock);
	end(data);
	return (NULL);
}

bool	soul_rejected(t_data *data, int i, time_t now, bool *all_eaten)
{
	pthread_mutex_lock(&data->meal_lock);
	if (data->args.max_meals < 0
		|| data->philos[i].meals < data->args.max_meals)
		*all_eaten = false;
	if (now - data->philos[i].last_meal > data->args.time2die)
	{
		pthread_mutex_unlock(&data->meal_lock);
		death(data, now, i);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (false);
}

void	*grim_reaper(void *arg)
{
	t_data	*data;
	bool	all_eaten;
	int		i;
	time_t	now;

	data = arg;
	while (!is_simulation_over(data))
	{
		all_eaten = true;
		now = current_time_ms();
		i = 0;
		while (i < data->args.philos_nb && !is_simulation_over(data))
		{
			if (soul_rejected(data, i, now, &all_eaten))
				return (NULL);
			i++;
		}
		if (all_eaten && !is_simulation_over(data))
			end(data);
		usleep(1000);
	}
	return (NULL);
}
