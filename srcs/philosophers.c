/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:42:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/13 22:27:13 by dnahon           ###   ########.fr       */
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
	return (current_time - data->start_time);
}

void	init_data(t_data *data, int ac, char **av)
{
	struct timeval	time;
	int				i;

	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->eat_requirement = atoi(av[5]);
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
		data->philos[i].state = THINKING;
		data->philos[i].data = data;
		i++;
	}
}

void	philo_eat(t_data *data, t_philo *philo)
{
	long	current_time;

	current_time = time_in_ms(data);
	philo->state = EATING;
	printf("%ld %d has taken a fork\n", current_time, philo->id);
	printf("%ld %d is eating\n", current_time, philo->id);
	usleep(data->time_to_eat * 1000);
	philo->last_meal_time = time_in_ms(data);
	philo->meals_eaten++;
}

void	philo_sleeping(t_data *data, t_philo *philo)
{
	long	current_time;

	current_time = time_in_ms(data);
	printf("%ld %d is sleeping\n", current_time, philo->id);
	philo->state = SLEEPING;
	usleep(data->time_to_sleep * 1000);
}

void	is_philo_dead(t_data *data, t_philo *philo)
{
	long	current_time;

	current_time = time_in_ms(data);
	if (current_time - philo->last_meal_time >= data->time_to_die)
	{
		philo->state = DEAD;
		data->someone_died = 1;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		left;
	int		right;
	long	current_time;

	philo = (t_philo *)arg;
	data = philo->data;
	left = philo->id;
	right = (philo->id + 1) % data->nb_philo;
	while (!data->someone_died)
	{
		is_philo_dead(data, philo);
		philo->state = THINKING;
		current_time = time_in_ms(data);
		printf("%ld %d is thinking\n", current_time, philo->id);
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->forks[right]);
		philo_eat(data, philo);
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
		philo_sleeping(data, philo);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			perror("Failed to create thread");
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			perror("Failed to join thread");
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		init_data(data, ac, av);
		init_philos(data);
		create_threads(data);
	}
	else
	{
		write(2, "Usage : ./philo nb_of_philos time_to_die time_to_eat ", 54);
		write(2, "time_to_sleep [eat_requirement]\n", 34);
	}
	return (0);
}
