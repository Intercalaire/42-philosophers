/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:21:40 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/11 12:21:41 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo(t_data *data, char **argv, int argc)
{
	data->philo->philo_nbr = ft_atol(argv[1]);
	data->last_meal = get_time();
	data->eat_count = 0;
	data->is_eating = 0;
	data->philo->time_to_die = ft_atol(argv[2]);
	data->philo->time_to_eat = ft_atol(argv[3]);
	data->philo->time_to_sleep = ft_atol(argv[4]);
	data->nb_meals = (argc == 6) ? ft_atol(argv[5]) : -1;
	data->died = 0;
	data->start_time = get_time();
	data->philo->left_fork = ft_calloc(sizeof(pthread_mutex_t) , data->philo->philo_nbr);
	if (!data->philo->left_fork)
		return (EXIT_FAILURE);
	data->philo->right_fork = ft_calloc(sizeof(pthread_mutex_t) , data->philo->philo_nbr);
	if (!data->philo->right_fork)
	{
		free(data->philo->left_fork);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
