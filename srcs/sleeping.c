/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:29:24 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/14 23:18:44 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_sleeping(t_data *data, t_philo *philo)
{
	print_message(data, philo, "is sleeping");
	ft_usleep(data, data->time_to_sleep);
}
