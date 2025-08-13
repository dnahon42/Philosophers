/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:42:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/13 16:43:00 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <bits/pthreadtypes.h>

long	time_in_ms(t_data *data)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->time_in_ms = current_time - data->time_begin;
	return (data->time_in_ms);
}

void	*routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(99700);
	pthread_mutex_lock(&data->mutex);
	data->time_in_ms = time_in_ms(data);
	pthread_mutex_unlock(&data->mutex);
	printf("Current time in ms : %ld\n", data->time_in_ms);
	return (arg);
}

int	are_all_philos_alive(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (data->p_state[i] == DEAD)
			return (0);
		i++;
	}
	return (1);
}

void	create_threads(t_data *data)
{
	pthread_t	*p_threads;
	int			i;

	p_threads = malloc(data->nb_of_philo * sizeof(pthread_t));
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (pthread_create(&p_threads[i], NULL, &routine, data) != 0)
			perror("Failed to create thread");
	}
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (pthread_join(p_threads[i], NULL) != 0)
			perror("Failed to join thread");
	}
	pthread_mutex_destroy(&data->mutex);
}

int	main(int ac, char **av)
{
	t_data			*data;
	struct timeval	time;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		memset(data, 0, sizeof(t_data));
		data->nb_of_philo = atoi(av[1]);
		data->time_to_die = atoi(av[2]);
		data->time_to_eat = atoi(av[3]);
		data->time_to_sleep = atoi(av[4]);
		data->forks_amount = data->nb_of_philo;
		gettimeofday(&time, NULL);
		data->time_begin = time.tv_sec * 1000 + time.tv_usec / 1000;
		if (ac == 6)
			data->eat_requirement = atoi(av[5]);
		create_threads(data);
	}
	else
	{
		write(2, "Usage : ./philo nb_of_philos ", 37);
		write(2, "time_to_die time_to_eat time_to_sleep ", 39);
		write(2, "[number_of_times_each_ philosopher_must_eat]", 45);
	}
}
