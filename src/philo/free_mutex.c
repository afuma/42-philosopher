/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:26:34 by edesaint          #+#    #+#             */
/*   Updated: 2023/10/19 14:51:35 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

void	free_locks(t_data *data)
{
	int	i;

	if (data->is_locks_destroy)
		return ;
	i = 0;
	if (data->locks)
	{
		while (i < 5)
		{
			pthread_mutex_destroy(&data->locks[i]);
			i++;
		}
		free(data->locks);
		data->locks = NULL;
	}
}

void	free_forks(t_data *data)
{
	int	i;

	if (data->is_forks_destroy)
		return ;
	i = 0;
	if (data->forks)
	{
		while (i < data->num_philosophers)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
}
