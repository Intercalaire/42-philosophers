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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

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
}				t_philo;

typedef struct s_data
{
	int				nb_meals; // number of meals
	int				last_meal; // time of the last meal
	int				eat_count; // number of meals eaten
	int				is_eating; // is the philosopher eating
	int				died; // is the philosopher dead
	int	start_time; // start time
	t_philo			*philo; // philosopher
}				t_data;

void	*philosopher(void *arg);
long	ft_atol(const char *nptr);
void	*ft_calloc( size_t nmemb, size_t size);
int		init_philo(t_data *data, char **argv, int argc);

#endif
