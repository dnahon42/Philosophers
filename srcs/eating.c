/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:28:14 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 16:30:52 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_data *data, t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % data->nb_philo;
	if (check_death_and_requirements(data) == 1)
		return ;
	pthread_mutex_lock(&data->forks[left]);
	print_message(data, philo, "has taken a fork");
	if (check_death_and_requirements(data) == 1)
		return (pthread_mutex_unlock(&data->forks[left]), (void)0);
	pthread_mutex_lock(&data->forks[right]);
	print_message(data, philo, "has taken a fork");
	if (check_death_and_requirements(data) == 1)
	{
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
		return ;
	}
}

void	philo_eat(t_data *data, t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % data->nb_philo;
	if (check_death_and_requirements(data) == 1)
		return ;
	take_forks(data, philo);
	if (check_death_and_requirements(data) == 1)
	{
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
		return ;
	}
	pthread_mutex_lock(&data->meal_mutex);
	print_message(data, philo, "is eating");
	philo->last_meal_time = time_in_ms(data);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks[left]);
	pthread_mutex_unlock(&data->forks[right]);
}
