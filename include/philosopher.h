/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 08:31:10 by blax              #+#    #+#             */
/*   Updated: 2023/10/19 14:45:53 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>

typedef enum e_state {
	THINKING,
	EATING,
	SLEEPING,
	TAKEN_FORK,
	DIED
}	t_state;

typedef enum e_state_ope {
	PLUS,
	MOINS
}	t_state_ope;

typedef enum e_state_lock {
	FINISH_MEAL,
	LAST_MEAL_TIME,
	PRINTING,
	IS_DIED,
	COUNT_MEAL
}	t_state_lock;

typedef struct s_phi
{
	int			id;
	long long	last_meal_time;
	pthread_t	thread;
}	t_phi;

struct	s_data;

typedef struct s_thread_args
{
	int				id;
	struct s_data	*data;
}	t_thread_args;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			is_died;
	int				max_eat;
	bool			*forks_initialized;
	long long		start_time;
	int				*count_meal;
	bool			stop_by_eating;
	bool			is_locks_destroy;
	bool			is_forks_destroy;
	bool			is_args_destroy;
	t_phi			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks;
	t_thread_args	**args_array;
}	t_data;

// eating.c
bool			ft_eating_pariter(t_data *data, int indice_philo, \
	int fork_1, int fork_2);
bool			ft_eating(t_data *data, int indice_philo);
void			operation_count_meal(t_data *data, int indice_philo, \
	t_state_ope operation);

// death_eating.c
bool			is_all_stop_by_eating(t_data *data);
bool			is_stop_by_eating(t_data *data);

// death.c
void			update_died(t_data *data, int indice_philo);
bool			is_dead(t_data *data);
bool			is_finish(t_data *data);
bool			is_dead_by_time(t_data *data, int indice_philo);

// error.c
int				handle_error(const char *msg, const char *type_msg);
int				ft_error(t_data *data, char *msg);

// free.c
void			free_philosophers(t_data *data, int i);
void			free_args(t_data *data);
void			free_all_resources(t_data *data, int i);

// free_mutex.c
void			free_locks(t_data *data);
void			free_forks(t_data *data);

// init_philosopher.c
int				init_philosophers(t_data *data);
int				init_param_for_routine(t_data *data);
int				init_multiple_philosophers(t_data *data);
int				init_single_philosopher(t_data *data, int indice_philo, \
	pthread_t *thread, t_thread_args *args);
int				init_count_meal(t_data *data);

// init.c
int				init_from_arguments(t_data *data, int argc, char *argv[]);
int				ft_init(t_data *data, int argc, char *argv[]);
int				init_count_meal(t_data *data);

// init_mutex.c
int				init_forks(t_data *data);
int				init_locks(t_data *data);
pthread_mutex_t	*allocate_memory_for_mutex(int nb_mutex);
int				init_mutex(pthread_mutex_t *mutex, int nb_mutex);

// thread.c
void			*ft_solo_dinner(t_data *data, int indice_philo);
bool			ft_thinking(t_data *data, int indice_philo);
void			*philosopher_function(void *arg);

// thread_utils.c
long long		get_time(t_data *data);
bool			ft_sleep(t_data *data, int time_duration);
void			log_state_philosopher(t_data *data, int indice_philo, \
	t_state state);

// parsing.c
bool			ft_isdigit(int c);
bool			is_number(char *str);
bool			param_is_number(char *argv[]);
int				parsing(int argc, char *argv[]);

// utils_parsing.c
bool			param_overflow_char(char *argv[]);
bool			is_overflow_char(char *str);
bool			is_valid_number(char *argv[]);
long int		ft_atol(const char *str);
int				ft_atoi(const char *str);

// philosopher.c
int				ft_main(int argc, char *argv[]);

// utils.c
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);

#endif