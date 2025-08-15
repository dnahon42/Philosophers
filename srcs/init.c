/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:26:14 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 20:28:00 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_vars(t_data *data, int ac, char **av)
{
	int	status;

	status = 0;
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo <= 0 || data->nb_philo > 200)
		status = 2;
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die <= 0)
		status = 1;
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat <= 0)
		status = 1;
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep <= 0)
		status = 1;
	data->eat_requirement = -1;
	if (ac == 6)
	{
		data->eat_requirement = ft_atoi(av[5]);
		if (data->eat_requirement <= 0)
			status = 1;
	}
	return (status);
}

int	init_data(t_data *data, int ac, char **av)
{
	struct timeval	time;
	int				i;
	int				status;

	if (verif_args(ac, av) == 1)
		return (1);
	t((i = -1, status = init_vars(data, ac, av), 0));
	if (status == 1 || status == 2)
		return (status);
	t((data->someone_died = 0, data->met_requirements = 0, 0));
	gettimeofday(&time, NULL);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
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

int	philo_threads(t_data *data, int i)
{
	if (pthread_create(&data->philos[i].thread, NULL, &routine,
			&data->philos[i]) != 0)
	{
		data->someone_died = 1;
		pthread_join(data->monitor_thread, NULL);
		while (--i >= 0)
			pthread_join(data->philos[i].thread, NULL);
		return (1);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	t((i = -1, data->someone_died = 0, 0));
	if (data->nb_philo == 1)
	{
		if (pthread_create(&data->philos[0].thread, NULL, &solo_philo,
				&data->philos[0]) != 0)
			return (1);
		return (pthread_join(data->philos[0].thread, NULL), 0);
	}
	if (pthread_create(&data->monitor_thread, NULL, &monitor, data) != 0)
		return (1);
	while (++i < data->nb_philo)
	{
		if (philo_threads(data, i) == 1)
			return (1);
	}
	t((pthread_join(data->monitor_thread, NULL), i = -1, 0));
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}
