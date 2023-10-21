/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosopher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:15:00 by blax              #+#    #+#             */
/*   Updated: 2023/10/21 15:29:59 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

int	init_philosophers(t_data *data)
{
	data->philosophers = malloc(data->num_philosophers * sizeof(t_phi));
	if (!data->philosophers)
		return (handle_error("philosophers", "memory"));
	data->args_array = malloc(data->num_philosophers * sizeof(t_thread_args *));
	if (!data->args_array)
		return (handle_error("args array", "memory"));
	if (init_param_for_routine(data) != 0)
	{
		free(data->args_array);
		data->args_array = NULL;
		data->is_args_destroy = true;
		return (handle_error("args array", "init"));
	}
	if (init_multiple_philosophers(data) != 0)
		return (2);
	return (0);
}

int	init_param_for_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->args_array[i] = malloc(sizeof(t_thread_args));
		if (!data->args_array[i])
		{
			while (i > 0)
			{
				i--;
				if (data->args_array[i])
					free(data->args_array[i]);
			}
			return (handle_error("args", "memory"));
		}
		data->args_array[i]->data = data;
		data->args_array[i]->id = i;
		i++;
	}
	return (0);
}

int	init_multiple_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (init_single_philosopher(data, i, \
			&data->philosophers[i].thread, data->args_array[i]) != 0)
		{
			free_philosophers(data, i);
			free(data->philosophers);
			data->philosophers = NULL;
			return (handle_error("Creation of threads failed !", ""));
		}
		i++;
	}
	return (0);
}

int	init_single_philosopher(t_data *data, int indice_philo, \
	pthread_t *thread, t_thread_args *args)
{
	t_phi	*phi;

	phi = &data->philosophers[indice_philo];
	phi->id = indice_philo + 1;
	pthread_mutex_lock(&data->locks[COUNT_MEAL]);
	data->count_meal[indice_philo] = 0;
	pthread_mutex_unlock(&data->locks[COUNT_MEAL]);
	pthread_mutex_lock(&data->locks[FINISH_MEAL]);
	data->stop_by_eating = false;
	pthread_mutex_unlock(&data->locks[FINISH_MEAL]);
	phi->last_meal_time = get_time(data);
	args->data->philosophers[indice_philo] = *phi;
	if (pthread_create(thread, NULL, philosopher_function, args) != 0)
		return (2);
	return (0);
}
