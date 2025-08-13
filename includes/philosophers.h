/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:14:50 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/13 22:21:29 by dnahon           ###   ########.fr       */
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

typedef enum e_state
{
    EATING,
    SLEEPING,
    THINKING,
    DEAD
} t_state;

typedef struct s_data t_data;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    pthread_t       thread;
    t_state         state;
    t_data          *data;
} t_philo;

struct s_data
{
    long            start_time;
    int             nb_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             eat_requirement;
    int             someone_died;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t meal_mutex;
    t_philo         *philos;
};

long	time_in_ms(t_data *data);
void	init_data(t_data *data, int ac, char **av);
void	init_philos(t_data *data);
void	*routine(void *arg);
void	create_threads(t_data *data);
void	philo_eat(t_data *data, t_philo *philo);
void	philo_sleeping(t_data *data, t_philo *philo);
void	is_philo_dead(t_data *data, t_philo *philo);

#endif