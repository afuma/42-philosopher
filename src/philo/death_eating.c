/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:24:48 by blax              #+#    #+#             */
/*   Updated: 2023/10/19 14:51:05 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

bool	is_stop_by_eating(t_data *data)
{
	pthread_mutex_lock(&data->locks[FINISH_MEAL]);
	if (data->stop_by_eating)
	{
		pthread_mutex_unlock(&data->locks[FINISH_MEAL]);
		return (true);
	}
	pthread_mutex_unlock(&data->locks[FINISH_MEAL]);
	return (false);
}

bool	is_all_stop_by_eating(t_data *data)
{
	int	i;

	i = 0;
	if (data->max_eat == -1)
		return (false);
	pthread_mutex_lock(&data->locks[COUNT_MEAL]);
	while (i < data->num_philosophers)
	{
		if (data->max_eat > 0 && \
			data->count_meal[i] < data->max_eat)
		{
			pthread_mutex_unlock(&data->locks[COUNT_MEAL]);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&data->locks[COUNT_MEAL]);
	pthread_mutex_lock(&data->locks[FINISH_MEAL]);
	data->stop_by_eating = true;
	pthread_mutex_unlock(&data->locks[FINISH_MEAL]);
	return (true);
}
