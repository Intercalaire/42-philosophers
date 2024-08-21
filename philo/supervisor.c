/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 04:35:09 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/21 04:35:10 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	supervise_philosophers(t_philo *philo, t_data *data);
static void	supervisor_check_satiated(t_philo *philo, t_data *data);
static void	supervisor_check_death(t_philo *philo, t_data *data);
static int	wait_for_threads(t_philo *philo, t_data *data);

static int	supervise_philosophers(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->is_dead_mutex);
	if (data->is_dead == 0)
	{
		pthread_mutex_unlock(&data->is_dead_mutex);
		pthread_mutex_lock(&data->philo_satiated_mutex);
		if (data->philo_satiated != data->number_of_philosophers)
		{
			pthread_mutex_unlock(&data->philo_satiated_mutex);
			supervisor_check_death(philo, data);
			if (data->nb_of_times_philo_must_eat != 0)
				supervisor_check_satiated(philo, data);
		}
		else
		{
			pthread_mutex_unlock(&data->philo_satiated_mutex);
			return (-1);
		}
	}
	else
	{
		pthread_mutex_unlock(&data->is_dead_mutex);
		return (-1);
	}
	return (0);
}

static int	wait_for_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	check_ft_routine(t_philo *philo, t_data *data)
{
	if (init_threads(philo, data) == -1)
		return (-1);
	while (1)
	{
		if (supervise_philosophers(philo, data) == -1)
			break ;
	}
	if (wait_for_threads(philo, data) == -1)
		return (-1);
	return (0);
}

static void	supervisor_check_death(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i == data->number_of_philosophers)
			i = 0;
		pthread_mutex_lock(&data->philo_satiated_mutex);
		if (get_current_time() - philo[i].last_time_eaten >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo_satiated_mutex);
			pthread_mutex_lock(&data->is_dead_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->is_dead_mutex);
			pthread_mutex_lock(&data->printf_mutex);
			printf("%ld %d died\n", get_timestamp(data->start_time),
				philo[i].id_philo);
			pthread_mutex_unlock(&data->printf_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philo_satiated_mutex);
		i++;
	}
}

static void	supervisor_check_satiated(t_philo *philo, t_data *data)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (j < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philo_satiated_mutex);
		if (philo[j].nb_meals_eaten >= data->nb_of_times_philo_must_eat)
			count++;
		pthread_mutex_unlock(&data->philo_satiated_mutex);
		j++;
	}
	pthread_mutex_lock(&data->philo_satiated_mutex);
	data->philo_satiated = count;
	if (data->philo_satiated >= data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->is_dead_mutex);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->is_dead_mutex);
	}
	pthread_mutex_unlock(&data->philo_satiated_mutex);
}
