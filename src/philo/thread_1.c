/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:15:00 by blax              #+#    #+#             */
/*   Updated: 2023/10/21 15:37:22 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

void	*ft_solo_dinner(t_data *data, int indice_philo)
{
	pthread_mutex_lock(&data->forks[0]);
	log_state_philosopher(data, indice_philo + 1, TAKEN_FORK);
	ft_sleep(data, data->time_to_die);
	pthread_mutex_unlock(&data->forks[0]);
	return (NULL);
}

bool	ft_thinking(t_data *data, int indice_philo)
{
	long long int	time;

	time = get_time(data);
	log_state_philosopher(data, indice_philo + 1, THINKING);
	if (data->time_to_eat > data->time_to_sleep)
		ft_sleep(data, data->time_to_eat - data->time_to_sleep + 5);
	else
		ft_sleep(data, 5);
	return (false);
}

void	*philosopher_function(void *arg)
{
	t_thread_args	*args;
	t_data			*data;
	int				indice_philo;

	args = (t_thread_args *) arg;
	data = args->data;
	indice_philo = args->id;
	if (data->num_philosophers == 1)
		return (ft_solo_dinner(data, indice_philo));
	log_state_philosopher(data, indice_philo + 1, THINKING);
	if (indice_philo % 2 != 0)
		ft_sleep(data, data->time_to_eat);
	while (!is_dead(data) && !is_stop_by_eating(data))
	{
		if (ft_eating(data, indice_philo))
			return (NULL);
		log_state_philosopher(data, indice_philo + 1, SLEEPING);
		if (ft_sleep(data, data->time_to_sleep))
			return (NULL);
		if (is_dead(data) || is_stop_by_eating(data))
			return (NULL);
		if (ft_thinking(data, indice_philo))
			return (NULL);
	}
	return (NULL);
}
