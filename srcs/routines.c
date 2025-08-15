/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:23:51 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 16:04:03 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_death_and_requirements(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died || data->met_requirements)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	long	current_time;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(data, 1);
	while (1)
	{
		if (check_death_and_requirements(data) == 1)
			break ;
		current_time = time_in_ms(data);
		philo_eat(data, philo);
		if (check_death_and_requirements(data) == 1)
			break ;
		philo_sleeping(data, philo);
		if (check_death_and_requirements(data) == 1)
			break ;
		print_message(data, philo, "is thinking");
	}
	return (NULL);
}

void	*solo_philo(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	print_message(data, philo, "has taken a fork");
	ft_usleep(data, data->time_to_die);
	print_message(data, philo, "is dead");
	pthread_mutex_unlock(&data->forks[philo->id]);
	return (NULL);
}
