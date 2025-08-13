/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:14:50 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/13 16:41:33 by dnahon           ###   ########.fr       */
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

typedef enum philosopher_state
{
    EATING = 0,
    SLEEPING = 1,
    THINKING = 2,
    DEAD = 3
} p_state;

typedef struct s_data
{
    long time_begin;
    long time_in_ms;
    pthread_t *philos;
    int nb_of_philo;
    int forks_amount;
    int time_to_sleep;
    int time_to_die;
    int time_to_eat;
    int eat_requirement;
    pthread_mutex_t mutex;
    pthread_mutex_t *forks;
    p_state *p_state;
    
} t_data;

#endif