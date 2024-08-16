/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:42:03 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/15 10:42:05 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	if (check_philo_is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (check_philo_is_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->printf_mutex);
		return ;
	}
	printf("%ld %d is sleeping\n", get_timestamp(philo->data->start_time),
		philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	if (check_philo_is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (check_philo_is_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->printf_mutex);
		return ;
	}
	printf("%ld %d is thinking\n", get_timestamp(philo->data->start_time),
		philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

void	ft_eat(t_philo *philo, t_data *data)
{
	if (check_philo_is_dead(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (check_philo_is_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->printf_mutex);
		return ;
	}
	printf("%ld %d is eating\n", get_timestamp(philo->data->start_time),
		philo->id_philo);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(&data->philo_satiated_mutex);
	philo->last_time_eaten = get_current_time();
	pthread_mutex_unlock(&data->philo_satiated_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&data->philo_satiated_mutex);
	philo->nb_meals_eaten++;
	philo->nb_forks = 0;
	pthread_mutex_unlock(&data->philo_satiated_mutex);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	philo->left_fork->is_used = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	philo->right_fork->is_used = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}
