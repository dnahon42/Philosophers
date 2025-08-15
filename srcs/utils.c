/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:25:37 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 19:17:27 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <limits.h>

long	ft_atoi(const char *str)
{
	long	nb;
	int		i;
	int		signe;

	nb = 0;
	i = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb > INT_MAX || nb * signe < INT_MIN)
			return (LONG_MAX);
		i++;
	}
	return (nb * signe);
}

long	time_in_ms(t_data *data)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time - data->start_time);
}

void	ft_usleep(t_data *data, long milliseconds)
{
	long	start;

	start = time_in_ms(data);
	while ((time_in_ms(data) - start) < milliseconds)
		usleep(500);
}

void	print_message(t_data *data, t_philo *philo, const char *message)
{
	if (check_death_and_requirements(data) == 1)
		return ;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d %s\n", time_in_ms(data), philo->id + 1, message);
	pthread_mutex_unlock(&data->print_mutex);
}

// void	print_message_debug(t_data *data, t_philo *philo, const char *message)
// {
// 	if (check_death_and_requirements(data) == 1)
// 		return ;
// 	pthread_mutex_unlock(&data->death_mutex);
// 	pthread_mutex_lock(&data->print_mutex);
// 	printf("%ld %d %s Meals eaten : %d\n", time_in_ms(data), philo->id + 1,
// 		message, philo->meals_eaten + 1);
// 	pthread_mutex_unlock(&data->print_mutex);
// }
