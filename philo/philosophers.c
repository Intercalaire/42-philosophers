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

int	for_one(t_data *data)
{
	data->start_time = get_time();
	while (1)
	{
		if (get_time() - data->last_meal > data->philo->time_to_die)
		{
			printf("%d %d %s\n", get_time() - data->start_time, data->philo->philo_nbr, DIED);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

// void	*philosopher(void *arg)
// {
// 	t_philo		*philo;
// 	pthread_t	monitor;

// 	philo = (t_philo *)arg;
// 	philo->last_meal = get_time();
// 	pthread_create(&monitor, NULL, &monitor_philo, philo);
// 	pthread_detach(monitor);
// 	while (1)
// 	{
// 		take_forks(philo);
// 		eat(philo);
// 		drop_forks(philo);
// 		sleep_philo(philo);
// 	}
// 	return (NULL);
// }
void free_tab(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	parsing_argv(int argc, char **argv)
{
	int	i;
	int	*tab;

	i = 0;
	tab = ft_calloc((argc - 1) , sizeof(int));
	while(argv[i])
	{
		tab[i] = ft_atol(argv[i]);
		if (tab[i] > INT_MAX  || tab[i] < INT_MIN)
			return (free_tab(tab), EXIT_FAILURE);
		i++;
	}
	return(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	if (argc < 5 || argc > 6)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (parsing_argv(argc, argv) == EXIT_FAILURE)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (init_philo(data, argv, argc) == EXIT_FAILURE)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (data->philo->philo_nbr == 1)
	{
		free(data);
		return (for_one(data));
	}
}
