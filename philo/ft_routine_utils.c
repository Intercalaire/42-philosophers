/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 05:03:23 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/14 05:03:25 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks_utils(t_philo *philo, t_fork *fork);
static void	take_forks_more_utils(t_philo *philo);

void	take_forks(t_philo *philo)
{
	usleep(100);
	while (philo->nb_forks < 2)
	{
		if (philo->id_philo % 2 == 0)
		{
			pthread_mutex_lock(&philo->left_fork->fork_mutex);
			if (check_philo_is_dead(philo) == 0
				&& philo->left_fork->is_used == 0)
				take_forks_utils(philo, philo->left_fork);
			pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			pthread_mutex_lock(&philo->right_fork->fork_mutex);
			if (check_philo_is_dead(philo) == 0
				&& philo->right_fork->is_used == 0)
				take_forks_utils(philo, philo->right_fork);
			pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		}
		else
			take_forks_more_utils(philo);
		if (check_philo_is_dead(philo) == 1)
			break ;
	}
	if (philo->nb_forks == 2)
		ft_eat(philo, philo->data);
}

static void	take_forks_more_utils(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	if (check_philo_is_dead(philo) == 0 && philo->right_fork->is_used == 0)
		take_forks_utils(philo, philo->right_fork);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	if (check_philo_is_dead(philo) == 0 && philo->left_fork->is_used == 0)
		take_forks_utils(philo, philo->left_fork);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
}

static void	take_forks_utils(t_philo *philo, t_fork *fork)
{
	philo->nb_forks++;
	if (philo->nb_forks == 1)
	{
		pthread_mutex_lock(&philo->data->printf_mutex);
		if (check_philo_is_dead(philo) == 0)
			printf("%ld %d has taken a fork\n",
				get_timestamp(philo->data->start_time), philo->id_philo);
		pthread_mutex_unlock(&philo->data->printf_mutex);
		fork->is_used = 1;
	}
	if (philo->nb_forks == 2)
	{
		pthread_mutex_lock(&philo->data->printf_mutex);
		if (check_philo_is_dead(philo) == 0)
			printf("%ld %d has taken a fork\n",
				get_timestamp(philo->data->start_time), philo->id_philo);
		pthread_mutex_unlock(&philo->data->printf_mutex);
		fork->is_used = 1;
	}
}

int	check_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	return (0);
}
