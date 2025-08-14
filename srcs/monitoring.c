/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:30:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/14 23:37:06 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_death(t_data *data, long now, int i)
{
	pthread_mutex_lock(&data->death_mutex);
	if (!data->someone_died)
	{
		data->someone_died = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d is dead\n", now, data->philos[i].id + 1);
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->meal_mutex);
}

int	check_eat_requirements(t_data *data, t_philo *philo)
{
	int	i;

	if (data->eat_requirement == -1)
		return (0);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (philo[i].meals_eaten < data->eat_requirement)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_mutex);
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	long	now;

	data = (t_data *)arg;
	while (!data->someone_died)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			now = time_in_ms(data);
			pthread_mutex_lock(&data->meal_mutex);
			if (now - data->philos[i].last_meal_time >= data->time_to_die)
				return (check_death(data, now, i), NULL);
			pthread_mutex_unlock(&data->meal_mutex);
		}
		if (check_eat_requirements(data, data->philos) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
