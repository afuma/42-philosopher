/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:51:25 by blax              #+#    #+#             */
/*   Updated: 2023/10/19 14:59:31 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

int	init_from_arguments(t_data *data, int argc, char *argv[])
{
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_died = false;
	data->max_eat = -1;
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	return (0);
}

int	ft_init(t_data *data, int argc, char *argv[])
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->start_time = (long long)(tv.tv_sec)*1000 + \
		(long long)(tv.tv_usec) / 1000;
	data->is_locks_destroy = false;
	data->is_forks_destroy = false;
	data->is_args_destroy = false;
	if (init_from_arguments(data, argc, argv) != 0)
		return (handle_error("arguments", "init"));
	if (init_forks(data) != 0)
		return (handle_error("forks", "init"));
	if (init_locks(data) != 0)
		return (handle_error("locks", "init"));
	if (init_count_meal(data) != 0)
		return (handle_error("countMeal array", "init"));
	if (init_philosophers(data) != 0)
		return (handle_error("philosophers", "init"));
	return (0);
}

int	init_count_meal(t_data *data)
{
	data->count_meal = malloc(data->num_philosophers * sizeof(int));
	if (!data->count_meal)
		return (handle_error("countMeal array", "memory"));
	return (0);
}
