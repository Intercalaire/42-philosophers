/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:41:21 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/12 07:41:23 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*
philo[i].data : Pointeur vers la structure de données commune.
philo[i].id_philo : Identifiant unique du philosophe (commence à 1).
philo[i].nb_meals_eaten : Nombre de repas mangés par le philosophe (initialisé à 0).
philo[i].nb_forks : Nombre de fourchettes détenues par le philosophe (initialisé à 0).
philo[i].last_time_eaten : Temps du dernier repas (initialisé à data->is_dead).
philo[i].left_fork : Pointeur vers la fourchette gauche.
*/
int initialization_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{	
		philo[i].data = data;
		philo[i].id_philo = i + 1;
		philo[i].nb_meals_eaten = 0;
		philo[i].nb_forks = 0;
		philo[i].last_time_eaten = data->is_dead;
		philo[i].left_fork = &data->forks[i];
		if (philo[i].id_philo == data->number_of_philosophers)
			philo[i].right_fork = &data->forks[0];
		else
			philo[i].right_fork = &data->forks[i + 1];
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->nb_of_times_philo_must_eat = 0;
	if (argv[5])
		data->nb_of_times_philo_must_eat = ft_atol(argv[5]);
	data->is_dead = 0;
	data->philo_satiated = 0;
	data->start_time = 0;
	data->forks = NULL;
	data->forks = ft_calloc(sizeof(t_fork), data->number_of_philosophers);
	if (!data->forks)
		return (-1);
	return (0);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->forks->fork_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->is_dead_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->philo_satiated_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->printf_mutex, NULL))
		return (1);
	return (0);
}
