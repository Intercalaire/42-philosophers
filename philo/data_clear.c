/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:40:28 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/16 16:40:30 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int free_all(t_data *data)
{
	if (data)
	{
		if (data->philo)
		{
			if (data->philo->left_fork)
				free(data->philo->left_fork);
			if (data->philo->right_fork)
				free(data->philo->right_fork);
			free(data->philo);
		}
		free(data);
	}
	return (EXIT_FAILURE);
}

