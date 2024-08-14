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

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = NULL;
	data = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
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
		free(data->forks);
		free(data);
		return (1);
	}
	if ((init_mutex(data) == -1) || (initialization_philo(philo, data) == -1))
	{
		free(philo);
		free(data->forks);
		free(data);
		return (1);
	}
	if (check_ft_routine(philo, data) == -1)
	{
		free(philo);
		free(data->forks);
		free(data);
		return (1);
	}
	free(philo);
	free(data->forks);
	free(data);
	printf("End of the program\n");
	return (0);
}
