/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:42:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/12 21:53:58 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	printf("%d\n", *(int *)arg);
	return (arg);
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
	// pthread_mutex_destroy(&mutex);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		memset(data, 0, sizeof(t_data));
		data->nb_of_philo = atoi(av[1]);
		data->time_to_die = atoi(av[2]);
		data->time_to_eat = atoi(av[3]);
		data->time_to_sleep = atoi(av[4]);
		data->forks_amount = data->nb_of_philo;
		if (ac == 6)
			data->eat_requirement = atoi(av[5]);
		create_threads(data);
	}
	else
	{
		write(2, "Usage : ./philosophers nb_of_philos ", 37);
		write(2, "time_to_die time_to_eat time_to_sleep ", 39);
		write(2, "[number_of_times_each_ philosopher_must_eat]", 45);
	}
}
