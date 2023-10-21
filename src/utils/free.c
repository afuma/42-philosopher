/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 22:22:49 by blax              #+#    #+#             */
/*   Updated: 2023/10/21 15:30:58 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

void	free_philosophers(t_data *data, int i)
{
	if (data->philosophers)
	{
		while (i > 0)
		{
			i--;
			if (data->philosophers[i].thread)
				pthread_join(data->philosophers[i].thread, NULL);
		}
		free(data->philosophers);
		data->philosophers = NULL;
	}
}

void	free_args(t_data *data)
{
	int	i;

	if (data->is_args_destroy)
		return ;
	i = 0;
	if (data->args_array)
	{
		while (i < data->num_philosophers)
		{
			if (data->args_array[i])
				free(data->args_array[i]);
			i++;
		}
		free(data->args_array);
		data->args_array = NULL;
	}
}

void	free_all_resources(t_data *data, int i)
{
	free_philosophers(data, i);
	free_locks(data);
	free(data->count_meal);
	free_forks(data);
	free_args(data);
}
