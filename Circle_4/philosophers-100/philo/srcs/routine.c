/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:30:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 14:11:23 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals++;
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->data->meal_lock);
	usleep(philo->data->args.time2eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals++;
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->data->meal_lock);
	usleep(philo->data->args.time2eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	handle_lonely_philo(t_philo *philo)
{
	const char	*messages[] = {\
		"has taken a fork", \
		"is thinking: *I can't eat those pasta with only one fork*", \
		"is thinking: *I'm so hungry*", \
		"is thinking: *I'm starving*" \
	};
	long		interval;
	int			i;

	interval = philo->data->args.time2die / 5;
	i = 0;
	while (i < 4)
	{
		print_status(philo, messages[i]);
		usleep(interval * 1000);
		i++;
	}
	while (!is_simulation_over(philo->data))
		usleep(1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->data->args.philos_nb == 1)
	{
		handle_lonely_philo(philo);
		return (NULL);
	}
	while (!is_simulation_over(philo->data))
	{
		print_status(philo, "is thinking");
		usleep(1000);
		if (philo->id % 2 == 0)
			eat_even(philo);
		else
			eat_odd(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->args.time2sleep * 1000);
	}
	return (NULL);
}
