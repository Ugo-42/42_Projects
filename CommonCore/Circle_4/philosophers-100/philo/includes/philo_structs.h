/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:22:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/15 12:03:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include <pthread.h>

/* STRUCTS */
typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_args
{
	int	philos_nb;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	max_meals;
}	t_args;

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_philo
{
	t_data			*data;
	int				id;
	int				meals;
	time_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};

struct s_data
{
	t_args			args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	meal_lock;
	time_t			start_time;
	bool			simulation_end;
};

#endif
