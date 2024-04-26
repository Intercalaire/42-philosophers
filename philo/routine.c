/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:18:38 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/18 13:18:41 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	messages(char *str, t_data *data)
// {
// 	int	time;

// 	pthread_mutex_lock(&data->write);
// 	time = 0;
// 	ft_usleep(data->start_time + 1);
// 	if (ft_strcmp(DIED, str) == 0 && data->died == 0)
// 	{
// 		printf("%d %d %s\n", time, data->nb_meals, str);
// 		data->died = 1;
// 	}
// 	if (!data->died)
// 		printf("%d %d %s\n", time, data->nb_meals, str);
// 	pthread_mutex_unlock(&data->write);
// }

static void	ft_taken_a_fork(t_data *data)
{
	pthread_mutex_lock(data->philo->right_fork);
	printf(TAKE_FORKS);
	pthread_mutex_unlock(data->philo->left_fork);
	printf(TAKE_FORKS);
}
static void	drop_forks(t_data *data)
{
	pthread_mutex_unlock(data->philo->left_fork);
	pthread_mutex_unlock(data->philo->right_fork);
	printf(" drop taken a fork\n");;
	ft_usleep(data->philo->time_to_sleep);
}

static void	ft_is_thinking(t_data *data)
{
	pthread_mutex_lock(&data->philo->m_death);
	printf("%d %d %s\n", data->start_time, data->philo->philo_nbr, THINKING);
	pthread_mutex_unlock(&data->philo->m_death);
}

static void	ft_is_eating(t_data *data)
{
	ft_taken_a_fork(data);
	pthread_mutex_lock(&data->lock);
	data->is_eating = 1;
	data->philo->time_to_die = data->philo->time_to_die;
	printf(EATING"\n");
	data->eat_count++;
	ft_usleep(data->philo->time_to_eat);
	data->philo->time_to_die = 0;
	pthread_mutex_unlock(&data->lock);
	drop_forks(data);
}

void	*ft_routine(t_data *data)
{
	while (1)
	{
		ft_taken_a_fork(data);
		ft_is_eating(data);
		drop_forks(data);
		ft_is_thinking(data);
		pthread_mutex_lock(&data->philo->m_death);
		pthread_mutex_unlock(&data->philo->m_death);
	}
	return (NULL);
}