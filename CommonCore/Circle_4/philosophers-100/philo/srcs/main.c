/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:17:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/02 09:22:01 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	start_simulation(t_data *data, pthread_t *grim_reaper_thread)
{
	int	i;

	pthread_create(grim_reaper_thread, NULL, grim_reaper, data);
	i = 0;
	while (i < data->args.philos_nb)
	{
		pthread_create(
			&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i += 2;
	}
	i = 1;
	while (i < data->args.philos_nb)
	{
		pthread_create(
			&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i += 2;
	}
}

static void	end_simulation(t_data *data, pthread_t grim_reaper_thread)
{
	int	i;

	pthread_join(grim_reaper_thread, NULL);
	i = 0;
	while (i < data->args.philos_nb)
	{
		pthread_join(data->philos[i++].thread, NULL);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->meal_lock);
	i = 0;
	while (i < data->args.philos_nb)
	{
		pthread_mutex_destroy(&data->forks[i++]);
	}
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	pthread_t	grim_reaper_thread;
	t_data		data;

	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (1);
	}
	if (!parse_args(&data.args, argc, argv))
		return (1);
	if (!init_data(&data))
		return (1);
	start_simulation(&data, &grim_reaper_thread);
	end_simulation(&data, grim_reaper_thread);
	return (0);
}
