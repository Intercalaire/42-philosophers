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

void	*philo_routine(void *arg)
{
	t_philo *philosopher = (t_philo *)arg;
	t_data *data = philosopher->data;

	while (data->keep_iterating)
	{
		// Is thinking
		change_philo_state(philosopher, THINK);
		print_philo_action(philosopher, "is thinking");
		sleep_for(data->sleep_time);

		// Take a fork
		pthread_mutex_lock(philosopher->left_fork);
		change_philo_state(philosopher, EATING);
		print_philo_action(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->right_fork);
		print_philo_action(philosopher, "has taken a fork");

		// Is eating
		print_philo_action(philosopher, "is eating");
		pthread_mutex_lock(&philosopher->mut_last_eat_time);
		philosopher->last_eat_time = get_time_in_ms();
		pthread_mutex_unlock(&philosopher->mut_last_eat_time);
		sleep_for(data->eat_time);

		// Put down the forks
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);

		// Check if philosopher is full
		pthread_mutex_lock(&philosopher->mut_meals_eaten);
		philosopher->meals_eaten++;
		if (philosopher->meals_eaten >= data->nb_meals)
		{
			change_philo_state(philosopher, FULL);
			printf("Philosopher %d is full\n", philosopher->id);
			data->nb_full_p++;
			pthread_mutex_unlock(&philosopher->mut_meals_eaten);
			break;
		}
		pthread_mutex_unlock(&philosopher->mut_meals_eaten);

		// Is sleeping
		change_philo_state(philosopher, SLEEPING);
		print_philo_action(philosopher, "is sleeping");
		sleep_for(data->sleep_time);
	}

	return (NULL);
}