/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 05:11:59 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/13 05:12:01 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		if (check_philo_is_dead(philo) == 1)
			return (NULL);
		take_forks(philo);
		if (check_philo_is_dead(philo) == 1)
			return (NULL);
		ft_sleep(philo);
		if (check_philo_is_dead(philo) == 1)
			return (NULL);
		ft_think(philo);
	}
	return (NULL);
}

int	init_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread_id, NULL, (void *)ft_routine,
				&philo[i]))
			return (-1);
		i++;
	}
	return (0);
}
