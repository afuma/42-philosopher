/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:03:14 by edesaint          #+#    #+#             */
/*   Updated: 2023/10/19 15:02:08 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

int	init_forks(t_data *data)
{
	data->forks = allocate_memory_for_mutex(data->num_philosophers);
	if (!data->forks)
		return (handle_error("forks", "memory"));
	if (init_mutex(data->forks, data->num_philosophers) != 0)
	{
		free(data->forks);
		data->forks = NULL;
		data->is_forks_destroy = true;
		return (handle_error("forks", "init_mutex"));
	}
	return (0);
}

int	init_locks(t_data *data)
{
	data->locks = allocate_memory_for_mutex(5);
	if (!data->locks)
		return (handle_error("locks", "memory"));
	if (init_mutex(data->locks, 5) != 0)
	{
		free(data->locks);
		data->locks = NULL;
		data->is_locks_destroy = true;
		return (handle_error("locks", "init_mutex"));
	}
	return (0);
}

pthread_mutex_t	*allocate_memory_for_mutex(int nb_mutex)
{
	return (malloc(sizeof(pthread_mutex_t) * nb_mutex));
}

int	init_mutex(pthread_mutex_t *mutex, int nb_mutex)
{
	int	i;

	i = 0;
	while (i < nb_mutex)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&mutex[i]);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}
