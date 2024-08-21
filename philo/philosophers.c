/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:45:45 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/10 12:54:28 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_main(t_data *data, t_philo *philo);
static void	free_all(t_philo *philo, t_data *data, int what);
static void	destroy_mutex(t_data *data);
static int	argc_test(int argc);

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	philo = NULL;
	if (argc_test(argc) == 1)
		return (1);
	if (parse_args(argv) == 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, argv) == -1)
	{
		free(data);
		return (1);
	}
	philo = ft_calloc(sizeof(t_philo), data->number_of_philosophers);
	if (!philo)
	{
		free_all(NULL, data, 0);
		return (1);
	}
	if (parse_main(data, philo) == 1)
		return (1);
	return (0);
}

static int	argc_test(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	return (0);
}

static int	parse_main(t_data *data, t_philo *philo)
{
	if ((init_mutex(data) == -1) || (initialization_philo(philo, data) == -1))
	{
		destroy_mutex(data);
		free_all(philo, data, 2);
		return (1);
	}
	if (check_ft_routine(philo, data) == -1)
	{
		destroy_mutex(data);
		free_all(philo, data, 2);
		return (1);
	}
	destroy_mutex(data);
	free_all(philo, data, 2);
	return (0);
}

static void	free_all(t_philo *philo, t_data *data, int what)
{
	if (what == 0)
	{
		if (data)
			free(data);
		if (data && data->forks)
			free(data->forks);
	}
	if (what == 2)
	{
		if (philo)
			free(philo);
		if (data && data->forks)
			free(data->forks);
		if (data)
			free(data);
	}
}

static void	destroy_mutex(t_data *data)
{
	if (pthread_mutex_destroy(&data->is_dead_mutex))
		pthread_mutex_destroy(&data->is_dead_mutex);
	if (pthread_mutex_destroy(&data->philo_satiated_mutex))
		pthread_mutex_destroy(&data->philo_satiated_mutex);
	if (pthread_mutex_destroy(&data->printf_mutex))
		pthread_mutex_destroy(&data->printf_mutex);
	if (pthread_mutex_destroy(&data->forks->fork_mutex))
		pthread_mutex_destroy(&data->forks->fork_mutex);
}
