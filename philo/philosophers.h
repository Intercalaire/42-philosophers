/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:53:01 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/10 12:55:27 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				fork_id;
	int				is_used;
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_philo_must_eat;
	int				is_dead;
	int				philo_satiated;
	long int		start_time;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	philo_satiated_mutex;
	pthread_mutex_t	printf_mutex;
	t_fork			*forks;
}					t_data;

typedef struct s_philo
{
	int				id_philo;
	int				nb_meals_eaten;
	int				nb_forks;
	long int		last_time_eaten;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
}					t_philo;

// main.c
int					main(int argc, char **argv);

// init.c
int					initialization_philo(t_philo *philo, t_data *data);
int					init_data(t_data *data, char **argv);
int					init_mutex(t_data *data);

// supervisor.c
int					check_ft_routine(t_philo *philo, t_data *data);
int					init_threads(t_philo *philo, t_data *data);

// parsing.c
long long			parse_args(char **argv);
void				*ft_calloc(size_t nmemb, size_t size);
long long			ft_atol(const char *str);

// time.c
long int			get_timestamp(long int start);
long int			get_current_time(void);
int					ft_usleep(size_t milliseconds);

// routine.c
int					check_ft_routine(t_philo *philo, t_data *data);
int					check_philo_is_dead(t_philo *philo);
void				take_forks(t_philo *philo);

// ft_action.c
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);
void				ft_eat(t_philo *philo, t_data *data);

#endif
