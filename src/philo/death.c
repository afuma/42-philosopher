/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:34:47 by edesaint          #+#    #+#             */
/*   Updated: 2023/10/19 14:48:59 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

void	update_died(t_data *data, int indice_philo)
{
	log_state_philosopher(data, indice_philo + 1, DIED);
	pthread_mutex_lock(&data->locks[IS_DIED]);
	data->is_died = true;
	pthread_mutex_unlock(&data->locks[IS_DIED]);
}

bool	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->locks[IS_DIED]);
	if (data->is_died)
	{
		pthread_mutex_unlock(&data->locks[IS_DIED]);
		return (true);
	}
	pthread_mutex_unlock(&data->locks[IS_DIED]);
	return (false);
}

bool	is_finish(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (is_dead_by_time(data, i))
			return (update_died(data, i), true);
		i++;
	}
	if (is_all_stop_by_eating(data))
		return (true);
	return (false);
}

bool	is_dead_by_time(t_data *data, int indice_philo)
{
	t_phi	*phi;

	phi = &data->philosophers[indice_philo];
	pthread_mutex_lock(&data->locks[LAST_MEAL_TIME]);
	if (get_time(data) - phi->last_meal_time >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->locks[LAST_MEAL_TIME]);
		return (true);
	}
	pthread_mutex_unlock(&data->locks[LAST_MEAL_TIME]);
	return (false);
}
