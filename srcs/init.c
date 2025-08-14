/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:26:14 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 00:04:22 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_data(t_data *data, int ac, char **av)
{
	struct timeval	time;
	int				i;

	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_requirement = ft_atoi(av[5]);
	else
		data->eat_requirement = -1;
	data->someone_died = 0;
	gettimeofday(&time, NULL);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		i++;
	}
}

void	create_threads(t_data *data)
{
	int	i;

	t((i = -1, data->someone_died = 0, 0));
	pthread_create(&data->monitor_thread, NULL, &monitor, data);
	if (data->nb_philo == 1)
	{
		pthread_create(&data->philos[0].thread, NULL, &solo_philo,
			&data->philos[0]);
		pthread_join(data->philos[0].thread, NULL);
		return ;
	}
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
		{
			pthread_join(data->philos[i].thread, NULL);
			perror("Failed to create thread");
		}
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		perror("Failed to join monitor thread");
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			perror("Failed to detach thread");
	}
}
