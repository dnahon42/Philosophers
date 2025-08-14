/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:42:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/14 23:39:34 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	cleanup(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
	free(data);
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
		cleanup(data);
	}
	else
	{
		write(2, "Usage : ./philo nb_of_philos time_to_die time_to_eat ", 54);
		write(2, "time_to_sleep [eat_requirement]\n", 34);
	}
	return (0);
}
