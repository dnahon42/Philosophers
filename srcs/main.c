/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:42:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/15 19:45:33 by dnahon           ###   ########.fr       */
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
	int		init_data_value;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		init_data_value = init_data(data, ac, av);
		if (init_data_value == 1)
			return (free(data), write(2, "Invalid Arguments\n", 18), 1);
		else if (init_data_value == 2)
			return (free(data), write(2, PHILO_AMOUNT, 50), 1);
		init_philos(data);
		if (create_threads(data) == 1)
			return (cleanup(data), 1);
		cleanup(data);
	}
	else
	{
		write(2, "Usage : ./philo nb_of_philos time_to_die time_to_eat ", 54);
		write(2, "time_to_sleep [eat_requirement]\n", 34);
	}
	return (0);
}
