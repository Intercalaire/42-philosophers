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

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking *pensive"
# define SLEEPING "is sleeping *rompich"
# define EATING "is eating *crunch"
# define DIED "died :("

typedef struct s_philo
{
	int				philo_nbr; // nbr of the philosopher and fork
	int				time_to_die; // time to die
	int				time_to_eat; // time to eat
	int				time_to_sleep; // time to sleep
	pthread_mutex_t	*left_fork; // left fork
	pthread_mutex_t	*right_fork; // right fork
	pthread_mutex_t	m_death; // mutex death
}				t_philo;

typedef struct s_data
{
	int				nb_meals; // number of meals
	bool			keep_iterating; // keep iterating
	int				last_meal; // time of the last meal
	int				eat_count; // number of meals eaten
	int				is_eating; // is the philosopher eating
	int				died; // is the philosopher dead
	int				start_time; // start time
	int				nb_philos; // number of philosophers
	t_philo			*philo; // philosopher
	pthread_t		*philo_ths; // philosopher threads
	pthread_mutex_t	write; // mutex write
	pthread_mutex_t	lock; // mutex 
}				t_data;

long	ft_atol(const char *nptr);
void	*ft_calloc( size_t nmemb, size_t size);
int		init_philo(t_data *data, char **argv, int argc);
int		for_one(t_data *data);
void	*ft_routine(t_data *data);
int		parsing_argv(int argc, char **argv);
int		free_all(t_data *data);
void	ft_usleep(int ms);
long long	timestamp(void);
int	ft_strcmp(const char *s1, const char *s2);

#endif
