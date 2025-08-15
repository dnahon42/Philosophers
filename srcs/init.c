/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:26:14 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 17:03:24 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	t(int a)
{
	(void)a;
}

int	verif_args(int ac, char **av)
{
	if (ft_isstring(av[1]) == 1)
		return (1);
	if (ft_isstring(av[2]) == 1)
		return (1);
	if (ft_isstring(av[3]) == 1)
		return (1);
	if (ft_isstring(av[4]) == 1)
		return (1);
	if (ac == 6)
	{
		if (ft_isstring(av[5]) == 1)
			return (1);
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	struct timeval	time;
	int				i;

	if (verif_args(ac, av) == 1)
		return (1);
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo > 200)
		return (2);
	t((i = -1, data->time_to_die = ft_atoi(av[2]), 0));
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->eat_requirement = -1;
	if (ac == 6)
		data->eat_requirement = ft_atoi(av[5]);
	t((data->someone_died = 0, data->met_requirements = 0, 0));
	gettimeofday(&time, NULL);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
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

void	create_threads(t_data *data)
{
	int	i;

	i = -1;
	data->someone_died = 0;
	if (data->nb_philo == 1)
	{
		pthread_create(&data->philos[0].thread, NULL, &solo_philo,
			&data->philos[0]);
		pthread_join(data->philos[0].thread, NULL);
		return ;
	}
	pthread_create(&data->monitor_thread, NULL, &monitor, data);
	while (++i < data->nb_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, &routine,
			&data->philos[i]);
	}
	pthread_join(data->monitor_thread, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].thread, NULL);
}
