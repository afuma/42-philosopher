/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:28:16 by edesaint          #+#    #+#             */
/*   Updated: 2023/10/20 23:30:33 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

bool	ft_eating_pariter(t_data *data, int indice_philo, \
	int fork_1, int fork_2)
{
	pthread_mutex_lock(&data->forks[fork_1]);
	log_state_philosopher(data, indice_philo + 1, TAKEN_FORK);
	pthread_mutex_lock(&data->forks[fork_2]);
	log_state_philosopher(data, indice_philo + 1, TAKEN_FORK);
	pthread_mutex_lock(&data->locks[LAST_MEAL_TIME]);
	data->philosophers[indice_philo].last_meal_time = get_time(data);
	pthread_mutex_unlock(&data->locks[LAST_MEAL_TIME]);
	log_state_philosopher(data, indice_philo + 1, EATING);
	operation_count_meal(data, indice_philo, PLUS);
	if (is_stop_by_eating(data))
	{
		pthread_mutex_lock(&data->locks[FINISH_MEAL]);
		data->stop_by_eating = true;
		pthread_mutex_unlock(&data->locks[FINISH_MEAL]);
	}
	operation_count_meal(data, indice_philo, MOINS);
	if (ft_sleep(data, data->time_to_eat))
	{
		pthread_mutex_unlock(&data->forks[fork_1]);
		pthread_mutex_unlock(&data->forks[fork_2]);
		return (true);
	}
	pthread_mutex_unlock(&data->forks[fork_1]);
	pthread_mutex_unlock(&data->forks[fork_2]);
	return (false);
}

bool	ft_eating(t_data *data, int indice_philo)
{
	int	fork_1;
	int	fork_2;

	fork_1 = indice_philo;
	fork_2 = (indice_philo + 1) % data->num_philosophers;
	if (indice_philo % 2 == 0)
	{
		if (ft_eating_pariter(data, indice_philo, fork_1, fork_2))
			return (true);
	}
	else
	{
		if (ft_eating_pariter(data, indice_philo, fork_2, fork_1))
			return (true);
	}
	operation_count_meal(data, indice_philo, PLUS);
	if (is_dead(data) || is_stop_by_eating(data))
		return (true);
	return (false);
}

void	operation_count_meal(t_data *data, int indice_philo, \
	t_state_ope operation)
{
	pthread_mutex_lock(&data->locks[COUNT_MEAL]);
	if (operation == PLUS)
		data->count_meal[indice_philo]++;
	else if (operation == MOINS)
		data->count_meal[indice_philo]--;
	pthread_mutex_unlock(&data->locks[COUNT_MEAL]);
}
