/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:14:50 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/14 23:17:35 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal_time;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

struct s_data
{
	long				start_time;
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_requirement;
	int					someone_died;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_t			monitor_thread;
	t_philo				*philos;
};

void	take_forks(t_data *data, t_philo *philo);
void	philo_eat(t_data *data, t_philo *philo);
void	init_data(t_data *data, int ac, char **av);
void	init_philos(t_data *data);
void	create_threads(t_data *data);
void	cleanup(t_data *data);
void	check_death(t_data *data, long now, int i);
int		check_eat_requirements(t_data *data, t_philo *philo);
void	*monitor(void *arg);
void	*routine(void *arg);
void	*solo_philo(void *arg);
void	philo_sleeping(t_data *data, t_philo *philo);
void	t(int a);
int		ft_atoi(const char *str);
long	time_in_ms(t_data *data);
void	ft_usleep(t_data *data, long milliseconds);
void	print_message(t_data *data, t_philo *philo, const char *message);

#endif