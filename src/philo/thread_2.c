/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:29:51 by blax              #+#    #+#             */
/*   Updated: 2023/10/21 14:03:24 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

long long	get_time(t_data *data)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (long long)(tv.tv_sec)*1000 + \
		(long long)(tv.tv_usec) / 1000;
	return (current_time - data->start_time);
}

bool	ft_sleep(t_data *data, int time_duration)
{
	int	time;

	time = get_time(data);
	while (get_time(data) - time < time_duration)
	{
		if (is_dead(data) || is_stop_by_eating(data))
			return (true);
		usleep(1000);
	}
	return (false);
}

void	log_state_philosopher(t_data *data, int num_philo, t_state state)
{
	long long	timestamp_in_ms;

	timestamp_in_ms = get_time(data);
	pthread_mutex_lock(&data->locks[PRINTING]);
	if (is_dead(data) || is_stop_by_eating(data))
	{
		pthread_mutex_unlock(&data->locks[PRINTING]);
		return ;
	}
	if (state == THINKING)
		printf("%lld %d is thinking\n", timestamp_in_ms, num_philo);
	else if (state == EATING)
		printf("%lld %d is eating\n", timestamp_in_ms, num_philo);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping\n", timestamp_in_ms, num_philo);
	else if (state == TAKEN_FORK)
		printf("%lld %d has taken a fork\n", timestamp_in_ms, num_philo);
	else if (state == DIED)
		printf("%lld %d died\n", timestamp_in_ms, num_philo);
	pthread_mutex_unlock(&data->locks[PRINTING]);
}
